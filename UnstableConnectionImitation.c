#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <ctype.h>
#include <tchar.h>
#include <psapi.h>

#define LSIZE 4

DWORD* ThreadF(DWORD, bool);
DWORD GetPID(char*);
void* read(void*);
void* read2(void*);
void* second(void*);
bool Switch = true;
bool press = false;
float lower1 = 4;
float upper1 = 9;
float lower2 = 3;
float upper2 = 6;
HWND Window;

char letter = 'T';

#ifdef _UNICODE
  #define tprintf wprintf
#else
  #define tprintf printf
#endif

int main(int ArgLength, char **Args) {
	Window = GetConsoleWindow();
	printf("Program was created by Daniel486638.\nSend L or S or 1 or 2 and then send your key for the hot key or change the mode (1 for switch and 0 for hold) or change the lower and upper bounds of the cooldowns respectively (for example, if you send L and then E, program will be activated by CTRL + E. If you send 1 and then 2 and then 3, then the cooldown between abscence of connections will be a random number from 2 to 3. If you send 2 and then 3 and then 4, time of no connection is a random number from 3 to 4).\n");//ShowWindow(Window, SW_HIDE);
	DWORD PID;
	//sscanf(Args[1], "%d", &PID);
	pthread_t *TID = (pthread_t*)malloc(sizeof(pthread_t));
	pthread_create(TID, NULL, read, NULL);

	pthread_t *TID2 = (pthread_t*)malloc(sizeof(pthread_t));
	pthread_create(TID2, NULL, read2, NULL);

	TCHAR filename[MAX_PATH];
	TCHAR command[MAX_PATH + 115];
	char str4num[8];

	srand(time(NULL));
	while (1) {
		if (press) {
			Sleep((int)(1000 * lower1));
			if (upper1 > lower1) {
				Sleep(rand() % (int)(1000 * (upper1 - lower1)));
			};

			if (!press) {
				continue;
			};

			DWORD TID = GetWindowThreadProcessId(Window, &PID);
			printf("\nPID: %i\nTID: %i\n", PID, TID);
			HANDLE PHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, PID);
			strcpy(command, "netsh advfirewall firewall add rule name=\"!Block ");

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
			CloseHandle(PHandle);

			Sleep((int)(1000 * lower2));
			if (upper2 > lower2) {
				Sleep(rand() % (int)(1000 * (upper2 - lower2)));
			};

			if (!press) {
				continue;
			};

			strcpy(command, "netsh advfirewall firewall delete rule name=\"!Block ");
			strcat(command, str4num);
			strcat(command, "\"");
			system(command);
			Beep(0x350, 300);
		};
		Sleep(2);
	};

	return 0;
};

void* read(void* v) {
	char string[15];
	char mode = 0;
	char list[LSIZE] = {'L', 'S', '1', '2'}; // list of commands
	bool isFound;

	while (1) {
		scanf("%s", string);
		switch (mode) {
			case 'L':
				letter = toupper(string[0]);
				mode = 0;
				break;
			case 'S':
				Switch = string[0] & 1;
				mode = 0;
				break;
			case '1':
				sscanf(string, "%f", &lower1);
				mode = '3';
				break;
			case '2':
				sscanf(string, "%f", &lower2);
				mode = '4';
				break;
			case '3':
				sscanf(string, "%f", &upper1);
				mode = 0;
				break;
			case '4':
				sscanf(string, "%f", &upper2);
				mode = 0;
				break;
			default:
				isFound = false;

				for (int i = 0; i < LSIZE; i++) {
					if (list[i] == toupper(string[0])) {
						mode = list[i];
						isFound = true;
					};
				};

				if (!isFound) {
					printf("Invalid");
				};
		};
	};
};

void* read2(void* v) {
	char string[2];
	char mode = 0;
	bool first = false;
	while (1) {
		if (GetAsyncKeyState(VK_CONTROL) < 0 && GetAsyncKeyState(letter) < 0) {
			if (Switch) {
				press = !press;
				if (press) {
					first = true;
				};
				while (GetAsyncKeyState(VK_CONTROL) < 0 && GetAsyncKeyState(letter) < 0) {
					Sleep(1);
				};
			} else {
				if (press == false) {
					first = true;
				};
				press = true;
			};
		} else if (!Switch) {
			press = false;
		};

		if (first) {
			Window = GetForegroundWindow();
			first = false;
		};

		Sleep(2);
	};
};