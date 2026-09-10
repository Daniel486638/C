#include <windows.h>
#define CHARCD 0
#define SCANCODE 0xE0

void Click(short, short);
void Press(unsigned char);
void KeyDown(unsigned char);
void KeyUp(unsigned char);
void TypeIn(char*);
void Enter(char*);
void Hold(unsigned char, unsigned short);
void OpenProgram(short, short, char*);
void GetBase(char*, POINT*);

int main() {
	HWND Window = GetConsoleWindow();
	ShowWindow(Window, SW_HIDE);
	Sleep(200);
	Click(611, 430);

	return 0;
};

void Click(short x, short y) {
	SetCursorPos(x, y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
};

void KeyDown(unsigned char Key) {
	keybd_event(Key, SCANCODE, 0, 0);
};

void KeyUp(unsigned char Key) {
	keybd_event(Key, SCANCODE, KEYEVENTF_KEYUP, 0);
};

void Press(unsigned char Key) {
	KeyDown(Key);
	KeyUp(Key);
};

void TypeIn(char Something[]) {
	for (int i = 0; i < strlen(Something); i++) {
		if (Something[i] >= 0x41 && Something[i] <= 0x5A) {
			KeyDown(VK_SHIFT);
			Press(Something[i]);
			KeyUp(VK_SHIFT);
		} else if (Something[i] >= 0x61 && Something[i] <= 0x7A) {
			Press(Something[i] - 0x20);
		} else {
			Press(Something[i]);
		};
		if (CHARCD) {
			Sleep(CHARCD);
		};
	};
};

void Enter(char Something[]) {
	TypeIn(Something);
	Press(VK_RETURN);
};

void Hold(unsigned char Key, unsigned short Time) {
	keybd_event(Key, 0, KEYEVENTF_EXTENDEDKEY, 0);
	Sleep(Time);
	keybd_event(Key, 0, KEYEVENTF_KEYUP, 0);
};

void OpenProgram(short x, short y, char Name[]) {
	Click(x, y);
	Sleep(10);
	Click(x, y);
	do {
		Sleep(70);
	} while (FindWindow(NULL, Name) == NULL);
	Sleep(140);
};

void GetBase(char Name[], POINT* Base) {
	HWND Window = FindWindow(NULL, Name);
	RECT Rect;
	GetWindowRect(Window, &Rect);
	Base->x = Rect.left;
	Base->y = Rect.top;
};