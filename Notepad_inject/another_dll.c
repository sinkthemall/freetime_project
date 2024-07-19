#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>

#pragma data_seg(".shared")
#pragma data_seg()
#pragma comment(linker, "/section:.shared,RWS")
LRESULT CALLBACK __declspec(dllexport) hookFunc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        // MessageBoxA(NULL, "IN", NULL, MB_OK);
        if (wParam == WM_DESTROY || wParam == WM_CLOSE || wParam == WM_QUIT || wParam == SC_CLOSE){
        // if (msg->message == WM_CLOSE) {
            // Logically, we should not spawn applications here; this is just for demonstration.
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
        }
    }
    // else MessageBoxA(NULL, "NO", NULL, MB_OK);
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        MessageBoxA(NULL, "DLL loaded!", NULL, MB_OK);
        // InstallHook();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
