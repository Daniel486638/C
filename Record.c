#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
// -lgdi32

#ifdef _UNICODE
  #define tprintf wprintf
#else
  #define tprintf printf
#endif

void GetOffset(HWND, short, short, POINT*);

int main() {
	if (!SetProcessDPIAware()) {
		MessageBox(0, "An error has occured.", "Error", MB_OKCANCEL | MB_ICONERROR);
		return 1;
	};
	POINT CursorPos;
	HDC DC = GetDC(NULL);
	char *Buffer;
	POINT Offset;
	COLORREF RGB;
	HWND Window;
	DWORD PID;
	DWORD TID;
	TCHAR filename[MAX_PATH];

	while (1) {
		if (GetAsyncKeyState(VK_CONTROL) < 0 && GetAsyncKeyState(0x51) < 0) {
			GetCursorPos(&CursorPos);
			RGB = GetPixel(DC, CursorPos.x, CursorPos.y);
			Window = GetForegroundWindow();
			GetOffset(Window, CursorPos.x, CursorPos.y, &Offset);
			GetWindowText(Window, Buffer, 26);
			tprintf("%s\n%i, %i\n%i, %i\n%i, %i, %i\n\n", Buffer, CursorPos.x, CursorPos.y, Offset.x, Offset.y, GetRValue(RGB), GetGValue(RGB), GetBValue(RGB));
			/*TID = GetWindowThreadProcessId(Window, &PID);
			printf("PID: %i\nTID: %i\n\n", PID, TID);
			HANDLE PHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, PID);

			if (PHandle != NULL) {
				if (GetModuleFileNameEx(PHandle, NULL, filename, MAX_PATH) == 0) {
					printf("Failed to get path.\n\n\n\n");
				} else {
					tprintf("%s\n\n\n\n", filename);
				};
			} else {
				printf("Failed to open process.\n\n\n\n");
			};*/
			
			while (GetAsyncKeyState(VK_CONTROL) < 0 && GetAsyncKeyState(0x51) < 0) {
				Sleep(1);
			};
		};
	};
	ReleaseDC(NULL, DC);
	
	return 0;
};

void GetOffset(HWND Window, short x, short y, POINT* Offset) {
	RECT Rect;
	GetWindowRect(Window, &Rect);
	Offset->x = x - Rect.left;
	Offset->y = y - Rect.top;
};