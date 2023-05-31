#pragma once
#include <common.hpp>
#include "signature/signature.hpp"

namespace engine {
	namespace hack {
		enum class DataType {
			Int,
			Float,
			Double
		};

		class ENGINE_API signature;
		class ENGINE_API proc {
			std::wstring m_name;
			DWORD m_pid{};

			HANDLE h_proc{};
			MODULEINFO module_info = { 0 };
			HMODULE h_module = nullptr;
			DWORD cbNeeded = 0;

			uintptr_t startAddress;
			uintptr_t endAddress;

			DWORD GetProcessIdByName(const std::wstring& name);

			struct thread {
				thread(proc& p_proc);
				~thread();
				bool attached = false;
			private:
				proc& proc;

				HANDLE h_thread{};
				DWORD targetMainThreadId{};

				DWORD GetMainThreadId(DWORD processId);
			public:
				CONTEXT context{};
				HANDLE get_thread() { return h_thread; }
				CONTEXT get_context() { return context; }
				DWORD get_mainthreadid() { return targetMainThreadId; }
			};
																					
		public:
			proc(std::wstring name);
			proc(DWORD pid);
			proc(DWORD pid, std::wstring name);
			~proc();
			
			thread* m_thread;
			signature* m_sigs;

			void attach();
			bool attached = false;
			int is_access = 0;

			DWORD get_pid() { return m_pid; }
			HANDLE get_proc() { return h_proc; }
			HANDLE get_hmodule() { return h_module; }
			std::wstring get_name() { return m_name;  }
			DWORD get_cbneeded() { return cbNeeded; }
			MODULEINFO get_moduleinfo() { return module_info; }
			CONTEXT get_context() { return m_thread->context; }
			uintptr_t get_rsp() { return m_thread->context.Rsp; }

			uintptr_t get_startAddress() { return (uintptr_t)module_info.lpBaseOfDll; }
			uintptr_t get_endAddress() { return get_startAddress() + module_info.SizeOfImage; }

			SIZE_T get_size() {
				PROCESS_MEMORY_COUNTERS_EX pmc;
				SIZE_T size = 0;

				if (GetProcessMemoryInfo(h_proc, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
					size = pmc.PrivateUsage;
				}

				return size;
			}

			void get_memoryRegion(uintptr_t& start, uintptr_t& end) {
				start = (uintptr_t)module_info.lpBaseOfDll;
				end = startAddress + module_info.SizeOfImage;
			}

			// Custom exception type for read failures
			struct ReadMemoryException : public std::exception {
				const char* what() const noexcept override {
					return "Failed reading process memory";
				}
			};

			bool read_success = false;
			template <typename T>
			T readProcMem(uintptr_t address) {
				T value;
				read_success = false;
				if (!ReadProcessMemory(h_proc, (LPCVOID)address, &value, sizeof(value), NULL)) {
					DWORD errorCode = GetLastError();
					EN_ASSERT("Failed reading process memory, error: {0}", errorCode);
					throw ReadMemoryException();
				}
				read_success = true;
				return value;
			}

			template <typename T>
			bool writeProcMem(uintptr_t address, T& value) {
				if (!WriteProcessMemory(h_proc, (LPVOID)address, &value, sizeof(value), NULL)) {
					DWORD errorCode = GetLastError();
					EN_ASSERT("Failed writing memory, error: {0}", errorCode);
					return false;
				}
				return true;
			}

			bool find_sig(const char* sig) {
				return m_sigs->scan(sig);
			}


			void error_handle(const char* error) {
				//EN_WARN("Error handled {0}", error);
				//EN_ASSERT("  process  : name {0} pid {1} : ", m_name, pid);
			}


		};

		class ENGINE_API baseAccessMemory {
		public:
			virtual ~baseAccessMemory() {}
			virtual bool writeMemory() = 0;
			virtual std::any readMemory() = 0;
			virtual DataType getSelectedType() = 0;
			virtual uint64_t getAddress() = 0;
			virtual void setAddress(uint64_t m_address) = 0;
			virtual void setWriteValue(std::any value) = 0;
			virtual std::any getReadValue() = 0;
		};

		template <typename T>
		struct ENGINE_API accessMemory : public baseAccessMemory {
			accessMemory(proc& m_proc, uintptr_t address, DataType selectedType) : m_proc(m_proc), address(address), selectedType(selectedType) {}

			proc& m_proc;
			uintptr_t address;
			DataType selectedType;

			T read = {};
			T write = {};

			bool writeMemory() override {
				if (m_proc.writeProcMem<T>(address, write)) // Pass address of 'write'
					return true;
				return false;
			}

			std::any readMemory() override {
				return m_proc.readProcMem<T>(address);
			}

			DataType getSelectedType() override { return selectedType; }
			uintptr_t getAddress() override { return address; }
			void setAddress(uintptr_t m_address) override { address = m_address; }
			std::any getReadValue() override { return read; }
			void setWriteValue(std::any value) override { write = std::any_cast<T>(value); }
		};



	}
}
