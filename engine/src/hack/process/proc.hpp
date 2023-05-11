#pragma once
#include <common.hpp>

namespace engine {
	class ENGINE_API proc {
		DWORD pid{};
		HANDLE h_proc{};

		std::wstring m_name;
		DWORD GetProcessIdByName(const std::wstring& name);

		struct thread {
			thread(proc p_proc);
			~thread();
			HANDLE get_thread() { return h_thread; }
		private:
			proc& proc;

			HANDLE h_thread{};

			HMODULE h_module = nullptr;
			DWORD cbNeeded = 0;

			MODULEINFO module_info = { 0 };

			CONTEXT context{};

			DWORD targetMainThreadId{};
			DWORD GetMainThreadId(DWORD processId);
		};

	public:
		thread* m_thred;

		proc(std::wstring name);
		proc(DWORD pid);
		~proc();

		void attach();

		DWORD get_pid() { return pid; }
		HANDLE get_proc() { return h_proc; }

		template <typename T>
		bool readProcMem(LPVOID address, T& value) {
			if (!ReadProcessMemory(h_proc, address, &value, sizeof(value), NULL)) {
				//const char* add = std::to_string(address).c_str();
				//EN_wARN("Failed reading Address: {0}", add);
				//error_handle("failed reading memory");
				return false;
			}
			return true;
		}

		template <typename T>
		bool writeProcMem(LPVOID address, T& value) {
			if (!WriteProcessMemory(h_proc, address, &value, sizeof(value), NULL)) {
				//const char* add = std::to_string(address).c_str();

				//EN_WARN("Failed reading Address: {0}", add);
				//error_handle("Failed writng memory");
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
