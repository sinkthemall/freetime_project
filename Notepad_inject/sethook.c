#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>

char dllPath[] = "D:\\freetime_project\\Notepad_inject\\another_dll.dll";
HMODULE hDLL;
HOOKPROC hookaddr;
typedef HMODULE(WINAPI *pLoadLibraryA)(LPCSTR lpLibFileName);

DWORD getGUI(DWORD pid) {
    printf("The process ID is %d!\n", pid);
    GUITHREADINFO info;
    info.cbSize = sizeof(GUITHREADINFO);
    DWORD tid = 0;

    HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
    THREADENTRY32 te32;
    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hThreadSnap == INVALID_HANDLE_VALUE) {
        printf("Failed to create snapshot!\n");
        return 0;
    }
    te32.dwSize = sizeof(THREADENTRY32);

    if (!Thread32First(hThreadSnap, &te32)) {
        printf("Failed to find first thread!\n");
        CloseHandle(hThreadSnap);         
        return 0;
    }
    // DWORD pid = GetCurrentProcessId();
    do {
        if (te32.th32OwnerProcessID == pid) {
            printf("Thread: %d\n", te32.th32ThreadID);
            if (GetGUIThreadInfo(te32.th32ThreadID, &info))
            {
                tid = te32.th32ThreadID;
                break;
            }
        }
    } while (Thread32Next(hThreadSnap, &te32));
    CloseHandle(hThreadSnap);
    printf("The GUI Thread ID is %d!\n", tid);
    return tid;
}


void inject(DWORD pid ,DWORD tid)
{
    if (tid == 0)
    {
        printf("Failed to install hook!\n");
        return ;
    }
    HHOOK hook = SetWindowsHookEx(WH_GETMESSAGE, hookaddr, hDLL, tid);
    if (!hook)
    {
        printf("Failed to install hook!\n");
    }
    else
    {
        printf("Hook installed!\n");
    }
}

int main()
{
    hDLL = LoadLibraryA(dllPath);
    hookaddr = (HOOKPROC) GetProcAddress(hDLL, "hookFunc");
    if (!hookaddr)
    {
        printf("function not found!\n");
        return 1;
    }

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
            inject(pe32.th32ProcessID, getGUI(pe32.th32ProcessID));
        }
    } while (Process32Next(hSnapshot, &pe32));
    int a;
    // scanf("%d", &a);
    while (1)
    {

    }
    FreeLibrary(hDLL);
    CloseHandle(hSnapshot);
    return 0;
}
