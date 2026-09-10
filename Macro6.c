#include <windows.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#define SHAKE 500

void Click();
void Hover(short x, short y);

char Speed = 50;

int main() {
	HWND Window = GetConsoleWindow();
	ShowWindow(Window, SW_HIDE);
	bool Bool = 0;
	bool Bool2 = 0;
	bool Pressed = 0;
	while (!Pressed) {
		if (Bool) {
			if (Bool2) {
				Hover(SHAKE, 0);
			} else {
				Hover(-SHAKE, 0);
			};
			Bool2 = !Bool2;
		};
		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(0x51)) {
			Bool = !Bool;
			while (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(0x51)) {
				Sleep(1);
			};
		};
		if (GetAsyncKeyState(VK_CONTROL)) {
			if (GetAsyncKeyState(71)) {
				Pressed = 1;
			};
		};
		Sleep(1);
	};
	

	return 0;
};

void Hover(short x, short y) {
	POINT CurrentPos;
	GetCursorPos(&CurrentPos);
	POINT Difference = {x, y};
	short Magnitude = abs(sqrt(pow(Difference.x, 2) + pow(Difference.y, 2)));
	double UnitX = (double)Difference.x / Magnitude;
	double UnitY = (double)Difference.y / Magnitude;
	for (int i = 1; i <= Magnitude; i += Speed) {
		SetCursorPos(CurrentPos.x + UnitX * i, CurrentPos.y + UnitY * i);
		Sleep(1);
	};
};