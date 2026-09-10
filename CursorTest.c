#include <windows.h>
#include <stdbool.h>

void Click(short, short);

int main() {
	HWND Window = GetConsoleWindow();
	ShowWindow(Window, SW_HIDE);

	Click(276, 846);

	bool Pressed;
	while (!Pressed) {
		if (GetAsyncKeyState(VK_CONTROL)) {
			if (GetAsyncKeyState(0x51)) {
				Click(1520, 20);
				Pressed = 1;
			};
		};
	};
	
	return 0;
};

void Click(short x, short y) {
	SetCursorPos(x, y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
};