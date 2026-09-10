#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, PTSTR cmdline,
                   int cmdshow) {
	// HANDLE Image = LoadImage(0, "Test.png");
	HWND Window = GetConsoleWindow();
	ShowWindow(Window, SW_HIDE);
	Window = CreateWindow("SCROLLBAR", "Test", WS_OVERLAPPEDWINDOW, 500, 500, 300, 300, 0, 0, hInstance, 0);
	ShowWindow(Window, SW_SHOW);
	UpdateWindow(Window);
	Sleep(5000);

	return 0;
};