#include "proc.hpp"

namespace engine {
    DWORD proc::GetProcessIdByName(const std::wstring& name) {
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snapshot == INVALID_HANDLE_VALUE) {
            return 0;
        }
        PROCESSENTRY32 entry = { 0 };
        entry.dwSize = sizeof(PROCESSENTRY32);
        if (!Process32First(snapshot, &entry)) {
            CloseHandle(snapshot);
            return 0;
        }
        DWORD pid = 0;
        do {
            if (name.compare(entry.szExeFile) == 0) {
                pid = entry.th32ProcessID;
                break;
            }
        } while (Process32Next(snapshot, &entry));

        CloseHandle(snapshot);
        return pid;
    }

    DWORD proc::thread::GetMainThreadId(DWORD processId) {
        HANDLE hThreadSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
        if (hThreadSnapshot == INVALID_HANDLE_VALUE)
            return 0;

        THREADENTRY32 te32;
        te32.dwSize = sizeof(THREADENTRY32);

        DWORD mainThreadId = 0;
        DWORD currentProcessId = GetCurrentProcessId();

        if (Thread32First(hThreadSnapshot, &te32)) {
            do {
                if (te32.th32OwnerProcessID == processId) {
                    mainThreadId = te32.th32ThreadID;
                    if (te32.th32OwnerProcessID == currentProcessId) {
                        break;  // Found the main thread of the target process in the same process
                    }
                }
            } while (Thread32Next(hThreadSnapshot, &te32));
        }

        CloseHandle(hThreadSnapshot);
        return mainThreadId;
    }

    proc::thread::thread(engine::proc& p_proc) : proc(p_proc) {
        targetMainThreadId = GetMainThreadId(proc.get_pid());
        if (targetMainThreadId == 0) {
            EN_WARN("Failed to get the main thread ID of the target process");
            return;
        }

        h_thread = OpenThread(THREAD_ALL_ACCESS, FALSE, targetMainThreadId);
        if (h_thread == NULL) {
            EN_WARN("Failed to open target thread");
            return;
        }

        context.ContextFlags = CONTEXT_FULL;
        if (!GetThreadContext(h_thread, &context)) {
            EN_WARN("Failed to get thread context");
            return;
        }

        attached = true;
    }

    proc::proc(std::wstring name) : m_name(name) {
        pid = GetProcessIdByName(name);
        //EN_INFO("waiting for process: {0}", name);
        while (pid == 0) {
            pid = GetProcessIdByName(name);
            Sleep(300);
        }
        
        attach();
        //EN_INFO("Attached to process   : name {0} pid {1} : ", m_name, pid);
    }

    proc::proc(DWORD pid) : pid(pid) {
        attach();
    }

    proc::thread::~thread() {
        CloseHandle(h_thread);
    }

    proc::~proc() {
        //delete m_thread;
        CloseHandle(h_proc);
    }

    void proc::attach() {
        //EN_INFO("waiting for process: {0}", name);

        //EN_INFO("Found process  : name {0} pid {1} : ", name, pid);

        h_proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
        if (h_proc == NULL) {
            EN_WARN("Not allowed to access process : pid {0} : ", pid);
            attached = false;
            is_access = 2;
            return;
        }

        m_thread = new thread(*this);

        // Get the module handle for the target module in the target process
        if (!EnumProcessModules(h_proc, &h_module, sizeof(h_module), &cbNeeded)) {
            EN_WARN("Failed to enumerate process modules");
            return;
        }

        // Allocate memory to store the module information
        if (!GetModuleInformation(h_proc, h_module, &module_info, sizeof(module_info))) {
            EN_WARN("Failed to get module information: {0}", GetLastError());
            return;
        }

        is_access = 1;
        attached = true;
    }
}