#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>

char dllPath[] = "D:\\freetime_project\\Notepad_inject\\my_dll.dll";

typedef HMODULE(WINAPI *pLoadLibraryA)(LPCSTR lpLibFileName);

void inject(DWORD pid)
{
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (hProcess == NULL)
    {
        printf("Failed to open process: Error %lu\n", GetLastError());
        return;
    }

    LPVOID mem = VirtualAllocEx(hProcess, NULL, strlen(dllPath) + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (!mem)
    {
        printf("Failed to allocate memory: Error %lu\n", GetLastError());
        CloseHandle(hProcess);
        return;
    }

    if (!WriteProcessMemory(hProcess, mem, dllPath, strlen(dllPath) + 1, NULL))
    {
        printf("Failed to write memory: Error %lu\n", GetLastError());
        VirtualFreeEx(hProcess, mem, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return;
    }

    HMODULE kernel32 = GetModuleHandleA("kernel32");
    if (kernel32 == NULL) {
        printf("Failed to get handle to kernel32.dll: Error %lu\n", GetLastError());
        VirtualFreeEx(hProcess, mem, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return;
    }

    pLoadLibraryA _LoadLibraryA = (pLoadLibraryA)GetProcAddress(kernel32, "LoadLibraryA");
    if (_LoadLibraryA == NULL) {
        printf("Failed to get address of LoadLibraryA: Error %lu\n", GetLastError());
        VirtualFreeEx(hProcess, mem, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return;
    }

    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)_LoadLibraryA, mem, 0, NULL);
    if (hThread == NULL)
    {
        printf("Failed to create remote thread: Error %lu\n", GetLastError());
        VirtualFreeEx(hProcess, mem, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return;
    }
    else {
        WaitForSingleObject(hThread, INFINITE);
    }

    VirtualFreeEx(hProcess, mem, 0, MEM_RELEASE);
    CloseHandle(hThread);
    CloseHandle(hProcess);
}

int main()
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Failed to create process snapshot: Error %lu\n", GetLastError());
        return 1;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hSnapshot, &pe32)) {
        fprintf(stderr, "Failed to get data for the first process: Error %lu\n", GetLastError());
        CloseHandle(hSnapshot);
        return 1;
    }

    do {
        if (strcmp(pe32.szExeFile, "Notepad.exe") == 0) {
            printf("Notepad PID: %u\n", pe32.th32ProcessID);
            inject(pe32.th32ProcessID);
        }
    } while (Process32Next(hSnapshot, &pe32));

    CloseHandle(hSnapshot);
    return 0;
}
