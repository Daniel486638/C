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
void* read(void*);
char letter;

int main(int ArgLength, char **Args) {
	HWND Window = GetConsoleWindow();
	printf("Program was created by Daniel486638.\nSend your key for the hot key (for example, if you send E, action will be activated by CTRL + E).\n");//ShowWindow(Window, SW_HIDE);
	DWORD PID;
	//sscanf(Args[1], "%d", &PID);
	while (1) {
		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState('D')) {
			SendInput();
			while (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(letter)) {
				Sleep(1);
			};
			ResumeThread(ThreadHandle);//ThreadF(PID, false);
			CloseHandle(ThreadHandle);
		};
		Sleep(1);
	};

	return 0;
};

void* read(void* v) {
	char string[2];
	while (1) {
		scanf("%s", string);
		letter = toupper(string[0]);
	};
};