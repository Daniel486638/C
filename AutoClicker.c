#include <windows.h>
#include <stdbool.h>
#include <stdio.h>

void Click();

int main() {
	HWND Window = GetConsoleWindow();
	ShowWindow(Window, SW_HIDE);
	bool Bool = 0;
	while (1) {
		if (Bool) {
			Click();
		};
		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(0x51)) {
			Bool = !Bool;
			while (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(0x51)) {
				Sleep(1);
			};
		};
		Sleep(1);
	};
	

	return 0;
};

void Click() {
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
};