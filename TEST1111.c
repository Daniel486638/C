#include <iostream>
#include <windows.h>

int main(int ArgLength, char **Args)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi; // The function returns this
	Sleep(4000);
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    CONST wchar_t* commandLine = TEXT("arg1 arg2 arg3");

    // Start the child process.
    if (!CreateProcessW(
        Args[0],      // app path
        (LPWSTR)commandLine,     // Command line 
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory
        &si,            // Pointer to STARTUPINFO structure
        &pi)           // Pointer to PROCESS_INFORMATION structure
        )
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
    }
    else
    {
        std::cout << "[          ] Successfully launched child process" << std::endl;
    }
}