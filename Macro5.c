#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CHARCD 0
#define SCANCODE 0xE0

short strfind(char[], char);
void Hover(short, short);
void Click(short, short);
void Press(unsigned char);
void KeyDown(unsigned char);
void KeyUp(unsigned char);
void TypeIn(char*);
void Enter(char*);
void Hold(unsigned char, unsigned short);

char Speed = 15;
char KeyCodes[] = "_1234567890-=_QWERTYUIOP[]___ASDFGHJKL;'ZXCVBNM,./";

int main() {
	if (!SetProcessDPIAware()) {
		MessageBox(0, "An error has occured.", "Error", MB_OKCANCEL | MB_ICONERROR);
		return 1;
	};
	HDC DC = GetDC(NULL);
	COLORREF RGB;
	HWND Window = GetConsoleWindow();
	ShowWindow(Window, SW_HIDE);
	while (!(GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState('Q'))) {
		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState('G')) {
			while (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState('G')) {
				Sleep(1);
			};
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		};
	};
	ReleaseDC(NULL, DC);

	return 0;
};

short strfind(char String[], char Character) {
	if (Character >= 0x61 && Character <= 0x7A) {
		Character -= 0x20;
	};
	for (int i = 0; i < strlen(String); i++) {
		if (String[i] == Character) {
			return i + 1;
		};
	};
	return -1;
};

void Hover(short x, short y) {
	POINT CurrentPos;
	GetCursorPos(&CurrentPos);
	POINT Difference = {x - CurrentPos.x, y - CurrentPos.y};
	short Magnitude = abs(sqrt(pow(Difference.x, 2) + pow(Difference.y, 2)));
	double UnitX = (double)Difference.x / Magnitude;
	double UnitY = (double)Difference.y / Magnitude;
	for (int i = 1; i <= Magnitude; i += Speed) {
		SetCursorPos(CurrentPos.x + UnitX * i, CurrentPos.y + UnitY * i);
		Sleep(1);
	};
};

void Click(short x, short y) {
	Hover(x, y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
};

void KeyDown(unsigned char Key) {
	keybd_event(Key, strfind(KeyCodes, Key), 0, 0);
};

void KeyUp(unsigned char Key) {
	keybd_event(Key, strfind(KeyCodes, Key) + 0x80, KEYEVENTF_KEYUP, 0);
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
	KeyDown(Key);
	Sleep(Time);
	KeyUp(Key);
};