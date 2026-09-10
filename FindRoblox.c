#include <stdio.h>
#include <windows.h>

int main() {
	HWND Window = FindWindow(NULL, "Roblox");
	if (Window == NULL) {
		printf("Window not found.");
		Sleep(1000);
		return 1;
	};
	DWORD PID;
	DWORD TID = GetWindowThreadProcessId(Window, &PID);
	printf("PID: %i\nTID: %i\n", PID, TID);
	RECT Rect;
	GetWindowRect(Window, &Rect);
	printf("Left: %i\nRight: %i\nTop: %i\nBottom: %i", Rect.left, Rect.right, Rect.top, Rect.bottom);
	getchar();

	return 0;
};