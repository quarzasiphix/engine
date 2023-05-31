#define HACK
#include "signature.hpp"

bool engine::hack::signature::scan(const char sig[]) {
    SIZE_T processSize = m_proc->get_size();
    unsigned char* processMemory = new unsigned char[processSize];

    SIZE_T bytesRead;
    ReadProcessMemory(m_proc->get_proc(), (LPCVOID)m_proc->get_startAddress(), processMemory, processSize, &bytesRead);

    int signatureSize = sizeof(sig) - 1;

    // Perform pattern scanning
    for (int i = 0; i < bytesRead - signatureSize + 1; ++i) {
        bool match = true;
        for (int j = 0; j < signatureSize; ++j) {
            if (processMemory[i + j] != sig[j] && sig[j] != '?') {
                match = false;
                break;
            }
        }

        if (match) {
            delete[] processMemory;

            // Calculate the offset based on the address of the variable within the pattern
            uintptr_t variableAddress = m_proc->get_startAddress() + i;
            uintptr_t variableOffset = variableAddress - m_proc->get_startAddress();

            uintptr_t absoluteAddress = m_proc->get_startAddress() + variableOffset;

            m_patterns.push_back(std::pair(sig, absoluteAddress));

            return true;
        }
    }

    delete[] processMemory;

    return false;
}