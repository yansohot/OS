#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cstring>

const int N = 24;

struct ProcessInfo {
    HANDLE hInputRead;
    HANDLE hInputWrite;
    HANDLE hOutputRead;
    HANDLE hOutputWrite;
    PROCESS_INFORMATION pi;
};

bool CreateProcessWithPipes(ProcessInfo& proc, const char* exeName) {
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&proc.hInputRead, &proc.hInputWrite, &sa, 0)) {
        std::cerr << "Failed to create input pipe for " << exeName << std::endl;
        return false;
    }

    if (!CreatePipe(&proc.hOutputRead, &proc.hOutputWrite, &sa, 0)) {
        std::cerr << "Failed to create output pipe for " << exeName << std::endl;
        return false;
    }

    STARTUPINFOA si;
    ZeroMemory(&si, sizeof(STARTUPINFOA));
    si.cb = sizeof(STARTUPINFOA);
    si.hStdInput = proc.hInputRead;
    si.hStdOutput = proc.hOutputWrite;
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    si.dwFlags = STARTF_USESTDHANDLES;

    ZeroMemory(&proc.pi, sizeof(PROCESS_INFORMATION));

    char cmdLine[MAX_PATH];
    strcpy(cmdLine, exeName);

    BOOL success = CreateProcessA(
        NULL,
        cmdLine,
        NULL,
        NULL,
        TRUE,
        0,
        NULL,
        NULL,
        &si,
        &proc.pi);

    if (!success) {
        std::cerr << "Failed to create process " << exeName
            << ". Error: " << GetLastError() << std::endl;
        return false;
    }

    CloseHandle(proc.hInputRead);
    CloseHandle(proc.hOutputWrite);

    std::cout << "Started process: " << exeName << " (PID: " << proc.pi.dwProcessId << ")" << std::endl;
    return true;
}

DWORD PipeToPipe(HANDLE hSource, HANDLE hDest) {
    const int BUFFER_SIZE = 4096;
    char buffer[BUFFER_SIZE];
    DWORD totalBytes = 0;
    DWORD bytesRead, bytesWritten;

    while (true) {
        if (!ReadFile(hSource, buffer, BUFFER_SIZE, &bytesRead, NULL)) {
            DWORD err = GetLastError();
            if (err == ERROR_BROKEN_PIPE) {
                break;
            }
            std::cerr << "ReadFile failed. Error: " << err << std::endl;
            break;
        }

        if (bytesRead == 0) {
            break;
        }

        totalBytes += bytesRead;

        if (!WriteFile(hDest, buffer, bytesRead, &bytesWritten, NULL)) {
            std::cerr << "WriteFile failed. Error: " << GetLastError() << std::endl;
            break;
        }

        if (bytesWritten != bytesRead) {
            std::cerr << "Warning: Not all bytes written (" << bytesWritten << " of " << bytesRead << ")" << std::endl;
        }
    }

    return totalBytes;
}

int main() {
    std::cout << "PIPELINE PROCESSES DEMONSTRATION" << std::endl;
    std::cout << "M: Multiply by 7" << std::endl;
    std::cout << "A: Add " << N << std::endl;
    std::cout << "P: Cube (x^3)" << std::endl;
    std::cout << "S: Sum all numbers" << std::endl;
    std::cout << std::endl;

    std::cout << "Enter numbers separated by spaces: ";
    std::string inputStr;
    std::getline(std::cin, inputStr);

    if (inputStr.empty()) {
        inputStr = "1 2 3 4 5";
        std::cout << "Using default input: " << inputStr << std::endl;
    }

    std::cout << std::endl << "Starting pipeline processes..." << std::endl;

    ProcessInfo procM, procA, procP, procS;

    if (!CreateProcessWithPipes(procM, "process_m.exe")) {
        return 1;
    }

    if (!CreateProcessWithPipes(procA, "process_a.exe")) {
        return 1;
    }

    if (!CreateProcessWithPipes(procP, "process_p.exe")) {
        return 1;
    }

    if (!CreateProcessWithPipes(procS, "process_s.exe")) {
        return 1;
    }

    std::cout << std::endl << "All processes started successfully!" << std::endl;
    std::cout << "Sending data to pipeline" << std::endl;

    std::string dataToSend = inputStr + "\n";
    DWORD bytesWritten;

    if (!WriteFile(procM.hInputWrite, dataToSend.c_str(), (DWORD)dataToSend.length(), &bytesWritten, NULL)) {
        std::cerr << "Failed to write to process_m.exe. Error: " << GetLastError() << std::endl;
    }
    else {
        std::cout << "Sent " << bytesWritten << " bytes to process_m.exe" << std::endl;
    }

    CloseHandle(procM.hInputWrite);

    std::cout << "Piping M -> A..." << std::endl;
    DWORD bytesMA = PipeToPipe(procM.hOutputRead, procA.hInputWrite);
    std::cout << "Transferred " << bytesMA << " bytes from M to A" << std::endl;
    CloseHandle(procM.hOutputRead);
    CloseHandle(procA.hInputWrite);

    std::cout << "Piping A -> P..." << std::endl;
    DWORD bytesAP = PipeToPipe(procA.hOutputRead, procP.hInputWrite);
    std::cout << "Transferred " << bytesAP << " bytes from A to P" << std::endl;
    CloseHandle(procA.hOutputRead);
    CloseHandle(procP.hInputWrite);

    std::cout << "Piping P -> S..." << std::endl;
    DWORD bytesPS = PipeToPipe(procP.hOutputRead, procS.hInputWrite);
    std::cout << "Transferred " << bytesPS << " bytes from P to S" << std::endl;
    CloseHandle(procP.hOutputRead);
    CloseHandle(procS.hInputWrite);

    std::cout << std::endl << "Reading final result from process S..." << std::endl;

    const int BUFFER_SIZE = 4096;
    char buffer[BUFFER_SIZE];
    DWORD bytesRead;
    std::string finalResult;

    while (ReadFile(procS.hOutputRead, buffer, BUFFER_SIZE, &bytesRead, NULL) && bytesRead > 0) {
        finalResult.append(buffer, bytesRead);
    }


    std::cout << "RESULT: " << finalResult;
    

    CloseHandle(procS.hOutputRead);

    std::cout << std::endl << "Waiting for processes to complete" << std::endl;

    WaitForSingleObject(procM.pi.hProcess, INFINITE);
    WaitForSingleObject(procA.pi.hProcess, INFINITE);
    WaitForSingleObject(procP.pi.hProcess, INFINITE);
    WaitForSingleObject(procS.pi.hProcess, INFINITE);

    DWORD exitCodeM, exitCodeA, exitCodeP, exitCodeS;
    GetExitCodeProcess(procM.pi.hProcess, &exitCodeM);
    GetExitCodeProcess(procA.pi.hProcess, &exitCodeA);
    GetExitCodeProcess(procP.pi.hProcess, &exitCodeP);
    GetExitCodeProcess(procS.pi.hProcess, &exitCodeS);

    std::cout << "Process exit codes:" << std::endl;
    std::cout << "  process_m.exe: " << exitCodeM << std::endl;
    std::cout << "  process_a.exe: " << exitCodeA << std::endl;
    std::cout << "  process_p.exe: " << exitCodeP << std::endl;
    std::cout << "  process_s.exe: " << exitCodeS << std::endl;

    CloseHandle(procM.pi.hProcess);
    CloseHandle(procM.pi.hThread);
    CloseHandle(procA.pi.hProcess);
    CloseHandle(procA.pi.hThread);
    CloseHandle(procP.pi.hProcess);
    CloseHandle(procP.pi.hThread);
    CloseHandle(procS.pi.hProcess);
    CloseHandle(procS.pi.hThread);

    std::cout << std::endl << "Pipeline execution completed successfully!" << std::endl;

    return 0;
}