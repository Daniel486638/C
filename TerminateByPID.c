#include <windows.h>
#include <stdio.h>

int main(int ArgLength, char **Args) {
	HWND Window = GetConsoleWindow();
	DWORD PID;
	sscanf(Args[1], "%d", &PID);
	if (IsWindow(Window)) {
		if (!TerminateProcess(OpenProcess(PROCESS_TERMINATE, 0, PID), 0)) {
			MessageBox(NULL, "Couldn't terminate a process.", "Error", MB_ICONERROR | MB_OK);
		};
	};
	

	return 0;
};