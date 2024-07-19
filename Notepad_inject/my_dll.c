#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <ctype.h>

void toLowerCase(char *str) {
    if (str == NULL) return; // Check for NULL pointer

    while (*str) {
        *str = tolower((unsigned char) *str); // Convert each character to lowercase
        str++; // Move to the next character
    }
}


typedef BOOL(WINAPI * pDestroyWindow)(HWND hWnd);
pDestroyWindow originalDestroyWindow;

BOOL WINAPI customDestroyWindow(HWND hWnd)
{
    PROCESS_INFORMATION pi; 
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    // Command line to execute calc.exe
    char commandLine[] = "calc.exe";
    if (!CreateProcess(NULL,   // No module name (use command line)
                       commandLine,          // Command line
                       NULL,                 // Process handle not inheritable
                       NULL,                 // Thread handle not inheritable
                       FALSE,                // Set handle inheritance to FALSE
                       0,                    // No creation flags
                       NULL,                 // Use parent's environment block
                       NULL,                 // Use parent's starting directory
                       &si,                  // Pointer to STARTUPINFO structure
                       &pi)) {               // Pointer to PROCESS_INFORMATION structure
        MessageBox(NULL, "Failed to start calculator.", "Error", MB_ICONERROR);
    } else {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    originalDestroyWindow(hWnd);
}

void InstallHook() {
    originalDestroyWindow = (pDestroyWindow)GetProcAddress(GetModuleHandleA("user32.dll"), "DestroyWindow");
    LPVOID imageBase = GetModuleHandleA(NULL);
    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER) imageBase;
    PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)((char *)imageBase + dosHeader->e_lfanew);
    IMAGE_DATA_DIRECTORY importsDirectory = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    PIMAGE_IMPORT_DESCRIPTOR importDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(importsDirectory.VirtualAddress + (DWORD_PTR)imageBase);

    LPCSTR libName = NULL;
    HMODULE hLib = NULL;
    PIMAGE_IMPORT_BY_NAME functionName = NULL;
    char dllname[0x200];
    for(; importDescriptor->Name; ++importDescriptor )
    {
        LPCSTR moduleName = (LPCSTR)((PBYTE)imageBase + importDescriptor->Name);
        sprintf(dllname, "%s", (char *) moduleName);
        toLowerCase(dllname);
        if (strcmp(dllname, "user32.dll"))
            continue;
        MessageBoxA(NULL, "Found dll", NULL, MB_OK);
        PIMAGE_THUNK_DATA originalFirstThunk = (PIMAGE_THUNK_DATA)((PBYTE)imageBase + importDescriptor->OriginalFirstThunk);
        PIMAGE_THUNK_DATA firstThunk = (PIMAGE_THUNK_DATA)((PBYTE)imageBase + importDescriptor->FirstThunk);
        while((originalFirstThunk->u1.AddressOfData) != NULL)
        {
            functionName = (PIMAGE_IMPORT_BY_NAME) ((PBYTE)imageBase + originalFirstThunk->u1.AddressOfData);
            if (!strcmp(functionName->Name, "DestroyWindow"))
            {
                DWORD oldProtect;
                VirtualProtect((LPVOID)(&firstThunk->u1.Function), 8, PAGE_READWRITE, &oldProtect);
                firstThunk->u1.Function = (DWORD_PTR)customDestroyWindow;
                MessageBoxA(NULL, "INstall hook success!", NULL, MB_OK);
            }
            originalFirstThunk++;
            firstThunk++;
        }
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        MessageBoxA(NULL, "INstalling Hook", NULL, MB_OK);
        InstallHook();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
