#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>
#include <tchar.h>
#include <psapi.h>

DWORD* ThreadF(DWORD, bool);
DWORD GetPID(char*);
void* read(void*);
void* second(void*);
bool Switch = true;

char letter = 'R';
char letter2 = VK_CONTROL;

#ifdef _UNICODE
  #define tprintf wprintf
#else
  #define tprintf printf
#endif

int main(int ArgLength, char **Args) {
	HWND Window = GetConsoleWindow();
	printf("Program was created by Daniel486638.\nSend 1 or 2 and then send your key for the hot key respectively (for example, if you send 1 and then E, block will be activated by CTRL + E).\n");//ShowWindow(Window, SW_HIDE);
	DWORD PID;
	//sscanf(Args[1], "%d", &PID);
	pthread_t *TID = (pthread_t*)malloc(sizeof(pthread_t));
	pthread_create(TID, NULL, read, NULL);
	TCHAR filename[MAX_PATH];
	TCHAR command[MAX_PATH + 115];
	char str4num[8];
	bool press = false;
	bool ruleAdded = false;
	bool suspended = false;

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

		if (press && !ruleAdded) {
			Window = GetForegroundWindow();
			DWORD TID = GetWindowThreadProcessId(Window, &PID);
			printf("\nPID: %i\nTID: %i\n", PID, TID);
			HANDLE PHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, PID);
			HANDLE ThreadHandle = OpenThread(THREAD_ALL_ACCESS, 0, TID);
			while (!(GetAsyncKeyState(letter2) < 0 && GetAsyncKeyState(letter) < 0)) {
			strcpy(command, "netsh advfirewall firewall add rule name=\"!Block ");
			ruleAdded = true;

			if (PHandle != NULL) {
				if (GetModuleFileNameEx(PHandle, NULL, filename, MAX_PATH) == 0) {
					printf("Failed to get path.\n");
				} else {
					tprintf("Path: %s\n", filename);
				};
			} else {
				printf("Failed to open process.\n");
			};

			sprintf(str4num, "%d", PID);
			strcat(command, str4num);
			strcat(command, "\" dir=out action=block program=\"");
			strcat(command, filename);
			strcat(command, "\" enable=yes");
			system(command);
			Beep(0x650, 300);
			if (suspended) {
				ResumeThread(ThreadHandle);
				suspended = false;
			};
			ThreadHandle = OpenThread(THREAD_ALL_ACCESS, 0, TID);
			for (int i = 0; i < 40; i++) {
				if (GetAsyncKeyState(letter2) < 0 && GetAsyncKeyState(letter) < 0) {
					break;
				};
				Sleep(100);
			};
			SuspendThread(ThreadHandle);
			suspended = true;
			strcpy(command, "netsh advfirewall firewall delete rule name=\"!Block ");
			strcat(command, str4num);
			strcat(command, "\"");
			system(command);
			Beep(0x350, 300);
			ruleAdded = false;
			}
			if (suspended) {
				ResumeThread(ThreadHandle);
				suspended = false;
			};
			CloseHandle(PHandle);
			CloseHandle(ThreadHandle);
		} else if (!press && ruleAdded) {
			strcpy(command, "netsh advfirewall firewall delete rule name=\"!Block ");
			strcat(command, str4num);
			strcat(command, "\"");
			system(command);
			Beep(0x350, 300);
			ruleAdded = false;
		};
		Sleep(5);
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
			mode = 0;
		} else if (mode == '2') {
			sscanf(string, "%x", &buffer);
			letter2 = buffer;
			mode = '0';
		} else if (mode == 'S') {
			//Switch = string[0] & 1;
			mode = 0;
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