#pragma once
#include <common.hpp>

namespace engine {
	class ENGINE_API proc {
		DWORD pid{};
		HANDLE h_proc{};
		MODULEINFO module_info = { 0 };
		HMODULE h_module = nullptr;
		DWORD cbNeeded = 0;

		uintptr_t startAddress;
		uintptr_t endAddress;

		std::wstring m_name;
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
		thread* m_thread;

		proc(std::wstring name);
		proc(DWORD pid);
		~proc();
		void attach();
		bool attached = false;
		int is_access = 0;

		DWORD get_pid() { return pid; }
		HANDLE get_proc() { return h_proc; }
		HANDLE get_hmodule() { return h_module; }
		std::wstring get_name() { return m_name;  }
		DWORD get_cbneeded() { return cbNeeded; }
		MODULEINFO get_moduleinfo() { return module_info; }
		CONTEXT get_context() { return m_thread->context; }
		uintptr_t get_rsp() { return m_thread->context.Rsp; }

		uintptr_t get_startAddress() { return (uintptr_t)module_info.lpBaseOfDll; }
		uintptr_t get_endAddress() { return get_startAddress() + module_info.SizeOfImage; }

		void get_address(uintptr_t& start, uintptr_t& end) {
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
		T readProcMem(LPVOID address) {
			T value;
			read_success = false;
			if (!ReadProcessMemory(h_proc, address, &value, sizeof(value), NULL)) {
				DWORD errorCode = GetLastError();
				EN_ASSERT("Failed reading process memory, error: {0}", errorCode);
				throw ReadMemoryException();
			}
			read_success = true;
			return value;
		}

		template <typename T>
		bool writeProcMem(LPVOID address, T& value) {
			if (!WriteProcessMemory(h_proc, address, &value, sizeof(value), NULL)) {
				DWORD errorCode = GetLastError();
				EN_ASSERT("Failed writing memory, error: {0}", errorCode);
				return false;
			}
			return true;
		}

		void error_handle(const char* error) {
			//EN_WARN("Error handled {0}", error);
			//EN_ASSERT("  process  : name {0} pid {1} : ", m_name, pid);
		}
	};
}
