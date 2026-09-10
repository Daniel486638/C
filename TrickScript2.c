#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>
// -lgdi32

#define FRAMECHANGETIME 50

void Click(short, short);
void ClickE(short, short);
void* read(void*);
char letter;
char letter2;
bool Switch = false;

int main(int ArgLength, char **Args) {
	if (!SetProcessDPIAware()) {
		MessageBox(0, "An error has occured.", "Error", MB_OKCANCEL | MB_ICONERROR);
		return 1;
	};
	HWND Window = GetConsoleWindow();
	printf("Program was created by Daniel486638.\nSend 1 or 2 and then send your key for the hot key number 1 or 2 respectively (for example, if you send 1 and then E, action will be activated by CTRL + E).\n");//ShowWindow(Window, SW_HIDE);
	DWORD PID;
	//sscanf(Args[1], "%d", &PID);
	letter = 'F';
	letter2 = VK_CONTROL;
	pthread_t *TID = (pthread_t*)malloc(sizeof(pthread_t));
	pthread_create(TID, NULL, read, NULL);
	bool press;
	bool started = false;
	HANDLE ThreadHandle;
	while (1) {
		if (GetAsyncKeyState(letter2) < 0 && GetAsyncKeyState(letter) < 0) {
			press = true;
			while (GetAsyncKeyState(letter2) < 0 && GetAsyncKeyState(letter) < 0) {
				Sleep(2);
			};
		};

		if (press) {
			Click(960, 529);
			press = false;
		};
		Sleep(2);
	};

	return 0;
};

void* read(void* v) {
	char string[3];
	char mode = 0;
	short buffer;
	while (1) {
		scanf("%s", string);
		if (mode == '1') {
			letter = toupper(string[0]);
			mode = '0';
		} else if (mode == '2') {
			sscanf(string, "%x", &buffer);
			letter2 = buffer;
			mode = '0';
		} else {
			if (toupper(string[0]) == '1') {
				mode = '1';
			} else if (toupper(string[0]) == '2') {
				mode = '2';
			} else {
				printf("Invalid.\n");
			};
		};
	};
};

void Click(short x, short y) {
	SetCursorPos(x, y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
};

void ClickE(short x, short y) {
	Click(x, y);
	Sleep(FRAMECHANGETIME);
};