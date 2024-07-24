#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <ctype.h>
#include <MinHook.h>

void toLowerCase(char *str) {
    if (str == NULL) return; // Check for NULL pointer

    while (*str) {
        *str = tolower((unsigned char) *str); // Convert each character to lowercase
        str++; // Move to the next character
    }
}


typedef BOOL(WINAPI * pDestroyWindow)(HWND hWnd);
pDestroyWindow originalDestroyWindow = NULL;

BOOL WINAPI customDestroyWindow(HWND hWnd)
{
    // MessageBoxA(NULL, "API Hooked", "Hooked", MB_OK);
    
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
    MH_DisableHook(GetProcAddress(GetModuleHandleA("user32"), "DestroyWindow"));
    originalDestroyWindow(hWnd);
}


void prepareHook() {
    if (MH_Initialize() != MH_OK)
    {
        MessageBoxA(NULL, "Failed to initialize", "Failed", MB_OK);
        return ;
    }
    if (MH_CreateHookApi(L"user32", "DestroyWindow", &customDestroyWindow, (LPVOID)&originalDestroyWindow) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to create hook API", "Failed", MB_OK);
        
    }
    // originalDestroyWindow = (pDestroyWindow)GetProcAddress(GetModuleHandleA("user32.dll"), "DestroyWindow");
    MH_EnableHook(GetProcAddress(GetModuleHandleA("user32"), "DestroyWindow"));

}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        MessageBoxA(NULL, "INstalling Hook", NULL, MB_OK);
        prepareHook();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
