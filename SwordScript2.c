#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>

DWORD* ThreadF(DWORD, bool);
DWORD GetPID(char*);
void Mouse(bool);
void* read(void*);
char letter;
char letter2;
bool Switch = true;

int main(int ArgLength, char **Args) {
	HWND Window = GetConsoleWindow();
	printf("Program was created by Daniel486638.\nSend 1 or 2 or s and then send your key for the hot key number 1 or 2 respectively or send the mode (1 for switch, 0 for hold) (for example, if you send 1 and then E, action will be activated by CTRL + E).\n");//ShowWindow(Window, SW_HIDE);
	DWORD PID;
	//sscanf(Args[1], "%d", &PID);
	letter = 'T';
	letter2 = VK_CONTROL;
	pthread_t *TID = (pthread_t*)malloc(sizeof(pthread_t));
	pthread_create(TID, NULL, read, NULL);
	bool press;
	bool started = false;
	HANDLE ThreadHandle;
	while (1) {
		if (GetAsyncKeyState(letter2) < 0 && GetAsyncKeyState(letter) < 0) {
			if (Switch) {
				press = !press;
				while (GetAsyncKeyState(letter2) < 0 && GetAsyncKeyState(letter) < 0) {
					Sleep(1);
				};
			} else {
				press = true;
			};
		} else if (!Switch) {
			press = false;
		};

		if (press && !started) {
			Window = GetForegroundWindow();
			DWORD TID = GetWindowThreadProcessId(Window, &PID);
			ThreadHandle = OpenThread(THREAD_ALL_ACCESS, 0, TID);
			Sleep(100);
			for (int i = 0; i <= 1; i++) {
				Mouse(true);
				Sleep(40);
				Mouse(false);
			};
			Sleep(400);
			SuspendThread(ThreadHandle);//ThreadF(PID, true);
			Sleep(600);
			ResumeThread(ThreadHandle);//ThreadF(PID, false);
			CloseHandle(ThreadHandle);
		};
		Sleep(1);
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
		} else if (mode == 'S') {
			Switch = string[0] & 1;
			mode = '0';
		} else {
			if (toupper(string[0]) == '1') {
				mode = '1';
			} else if (toupper(string[0]) == '2') {
				mode = '2';
			} else if (toupper(string[0]) == 'S') {
				mode = 'S';
			} else {
				printf("Invalid.\n");
			};
		};
	};
};

void Mouse(bool Down) {
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = XBUTTON1;
	DWORD A = MOUSEEVENTF_LEFTUP;
	if (Down) {
		A = MOUSEEVENTF_LEFTDOWN;
	};
	input.mi.dwFlags = A;
	SendInput(1, &input, sizeof(input));
};