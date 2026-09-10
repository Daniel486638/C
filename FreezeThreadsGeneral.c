#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>

DWORD* ThreadF(DWORD, bool, int);
DWORD GetPID(char*);
void* read(void*);
char letter;
char letter2;
bool Switch = false;
bool Exit = false;

int main(int ArgLength, char **Args) {
	HWND Window = GetConsoleWindow();
	printf("Program was created by Daniel486638.\nSend 1 or 2 or s and then send your key for the hot key number 1 or 2 respectively or send the mode (1 for switch, 0 for hold) (for example, if you send 1 and then E, action will be activated by CTRL + E).\n");//ShowWindow(Window, SW_HIDE);
	DWORD PID;
	unsigned int Num;
	sscanf(Args[1], "%d", &Num);
	printf("%i\n", Num);
	letter = 'R';
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
			ThreadF(PID, true, Num);
			started = true;
		} else if (!press && started) {
			ThreadF(PID, false, Num);
			started = false;
		};
		if (Exit) {
			break;
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
		if (toupper(string[0]) == 'E' && toupper(string[1]) == 'X') {
			Exit = true;
			break;
		};
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

DWORD* ThreadF(DWORD PID, bool Suspend, int Num){
	THREADENTRY32 Entry;
	Entry.dwSize = sizeof(THREADENTRY32);
	HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	unsigned int i = 0;
	if (Thread32First(Snapshot, &Entry)) {
		do {
			if (PID == 0) {
				printf("%i: %i\n", Entry.th32OwnerProcessID, Entry.th32ThreadID);
			} else if (Entry.th32OwnerProcessID == PID) {
				//printf("%i\n", Entry.th32ThreadID);
				HANDLE ThreadHandle = OpenThread(THREAD_ALL_ACCESS, 0, Entry.th32ThreadID);
				if (Suspend) {
					SuspendThread(ThreadHandle);
				} else {
					ResumeThread(ThreadHandle);
				};
				i++;
			};
		} while (Thread32Next(Snapshot, &Entry) && i < Num);
	};
	CloseHandle(Snapshot);
	return 0;
};