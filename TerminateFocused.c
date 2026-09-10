#include <windows.h>

int main() {
	HWND Window = GetConsoleWindow();
	ShowWindow(Window, SW_HIDE);
	while (1) {
		if (GetAsyncKeyState(VK_LMENU) && GetAsyncKeyState(VK_F4)) {
			while (GetAsyncKeyState(VK_LMENU) && GetAsyncKeyState(VK_F4)) {
				Sleep(1);
			};
			Window = GetForegroundWindow();
			DWORD PID;
			GetWindowThreadProcessId(Window, &PID);
			Sleep(8000);
			if (IsWindow(Window)) {
				if (!TerminateProcess(OpenProcess(PROCESS_TERMINATE, 0, PID), 0)) {
					MessageBox(NULL, "Couldn't terminate a process.", "Error", MB_ICONERROR | MB_OK);
				};
			};
		};
		Sleep(1);
	};
	

	return 0;
};