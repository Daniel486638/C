#include <stdio.h>
#include <windows.h>

int main() {
	HWND Window = GetConsoleWindow();
	ShowWindow(Window, SW_HIDE);
	if (!SetProcessDPIAware()) {
		MessageBox(0, "An error has occured.", "Error", MB_OKCANCEL | MB_ICONERROR);
		return 1;
	};
	POINT CursorPos;
	HDC DC = GetDC(NULL);
	COLORREF RGB;

	while (1) {
		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(0x51)) {
			if (GetAsyncKeyState(VK_SHIFT)) {
				break;
			};
			GetCursorPos(&CursorPos);
			for (int y = -100; y < 100; y++) {
				for (int x = -100; x < 100; x++) {
					SetPixel(DC, CursorPos.x + x, CursorPos.y + y, RGB(0, 0, 255));
				};
			};
			Sleep(100);
		};
	};
	ReleaseDC(NULL, DC);
	
	return 0;
};