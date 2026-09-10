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
float number;

int main(int ArgLength, char **Args) {
	HWND Window = GetConsoleWindow();
	printf("Program was created by Daniel486638.\nSend F or L or S and then send the value to change the FPS or letter for hotkey or mode (1 for switch mode, 0 for hold mode) respectively. (for example, if you send F and then 24, your FPS will be less or equal to 24.)\n");//ShowWindow(Window, SW_HIDE);
	DWORD PID;
	//sscanf(Args[1], "%d", &PID);
	letter = 'R';
	pthread_t *TID = (pthread_t*)malloc(sizeof(pthread_t));
	pthread_create(TID, NULL, read, NULL);
	number = 1000/(float)60;
	while (1) {
		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(letter)) {
			Window = GetForegroundWindow();
			DWORD TID = GetWindowThreadProcessId(Window, &PID);
			HANDLE ThreadHandle = OpenThread(THREAD_ALL_ACCESS, 0, TID);
			SuspendThread(ThreadHandle);//ThreadF(PID, true);
			Sleep(number);
			ResumeThread(ThreadHandle);//ThreadF(PID, false);
			CloseHandle(ThreadHandle);
		};
		Sleep(1);
	};

	return 0;
};

void* read(void* v) {
	char string[20];
	char mode = 0;
	while (1) {
		scanf("%s", string);
		if (mode == 'F') {
			sscanf(string, "%f", &number);
			number = ((float)1000)/number;
			mode = 0;
		} else if (mode == 'L') {
			letter = toupper(string[0]);
			mode = 0;
		} else {
			if (toupper(string[0]) == 'F') {
				mode = 'F';
			} else if (toupper(string[0]) == 'L') {
				mode = 'L';
			} else {
				printf("Invalid.\n");
			};
		};
	};
};