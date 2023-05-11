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

    proc::thread::thread(engine::proc p_proc) : proc(p_proc) {
        targetMainThreadId = GetMainThreadId(proc.get_pid());
        if (targetMainThreadId == 0) {
            proc.error_handle("Failed to get the main thread ID of the target process");
            return;
        }

        h_thread = OpenThread(THREAD_ALL_ACCESS, FALSE, targetMainThreadId);
        if (h_thread == NULL) {
            proc.error_handle("Failed to open target thread");
            return;
        }

        context.ContextFlags = CONTEXT_FULL;
        if (!GetThreadContext(h_thread, &context)) {
            proc.error_handle("Failed to get thread context");
            return;
        }
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
            error_handle("Failed to open process");
            return;
        }

        m_thred = new thread(*this);
    }
}