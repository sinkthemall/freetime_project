### What happen when press close window button?
-   Close button generate WM_CLOSE window message to window procedure of application

### Idea to spawn calc when close
-   Adding detors function (destructor function)
-   Intercept WM_CLOSE (SetWindowHookEx)
-   Patch DestroyWindow API IAT
-   Closing window event: https://learn.microsoft.com/en-us/windows/win32/learnwin32/closing-the-window
-   https://www.ired.team/offensive-security/code-injection-process-injection/import-adress-table-iat-hooking


### Note
-   DLL thread does not have privilege to install Hook to GUI thread
-   IAT patching: my_dll and codeinj
-   Hook window message: another_dll and sethook
-   Hook window message is not working (it does install the hook function to hook chain, but somehow no WM_CLOSE or WM_QUIT is found when close)
