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

char letter = 'R';
char letter2 = 'T';
bool Switch = true;

DWORD PID;

#ifdef _UNICODE
  #define tprintf wprintf
#else
  #define tprintf printf
#endif

int main(int ArgLength, char **Args) {
	HWND Window = GetConsoleWindow();
	printf("Program was created by Daniel486638.\nSend I or O or S and then send your key for the hot key for in or out or change the mode (1 for switch and 0 for hold) respectively (for example, if you send I and then E, in block will be activated by CTRL + E).\n");//ShowWindow(Window, SW_HIDE);
	//sscanf(Args[1], "%d", &PID);
	pthread_t *TID1 = (pthread_t*)malloc(sizeof(pthread_t));
	pthread_create(TID1, NULL, read, NULL);
	pthread_t *TID2 = (pthread_t*)malloc(sizeof(pthread_t));
	pthread_create(TID2, NULL, second, NULL);
	TCHAR filename[MAX_PATH];
	TCHAR command[MAX_PATH + 115];

	char str4num[8];
	bool press = false;
	bool ruleAdded = false;

	Sleep(2000);

	Window = GetForegroundWindow();
	DWORD TID = GetWindowThreadProcessId(Window, &PID);
	printf("\nPID: %i\nTID: %i\n", PID, TID);
	HANDLE PHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, PID);
	strcpy(command, "netsh advfirewall firewall add rule name=\"!BlockI ");

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
	strcat(command, "\" dir=in action=block program=\"");
	strcat(command, filename);
	strcat(command, "\" enable=no");
	system(command);

	strcpy(command, "netsh advfirewall firewall add rule name=\"!BlockO ");
	strcat(command, str4num);
	strcat(command, "\" dir=out action=block program=\"");
	strcat(command, filename);
	strcat(command, "\" enable=no");
	system(command);

	CloseHandle(PHandle);

	while (1) {
		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(letter)) {
			if (Switch) {
				press = !press;
				while (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(letter)) {
					Sleep(1);
				};
			} else {
				press = true;
			};
		} else if (!Switch) {
			press = false;
		};

		if (press && !ruleAdded) {
			strcpy(command, "netsh advfirewall firewall set rule name=\"!BlockI ");

			sprintf(str4num, "%d", PID);
			strcat(command, str4num);
			strcat(command, "\" new enable=yes");
			system(command);
			Beep(0x650, 300);
			ruleAdded = true;
		} else if (!press && ruleAdded) {
			strcpy(command, "netsh advfirewall firewall set rule name=\"!BlockI ");
			strcat(command, str4num);
			strcat(command, "\" new enable=no");
			system(command);
			Beep(0x350, 300);
			ruleAdded = false;
		};
		Sleep(5);
	};

	return 0;
};

void* read(void* v) {
	char string[2];
	char mode = 0;
	while (1) {
		scanf("%s", string);
		if (mode == 'I') {
			letter = toupper(string[0]);
			mode = 0;
		} else if (mode == 'O') {
			letter2 = toupper(string[0]);
			mode = 0;
		} else if (mode == 'S') {
			Switch = string[0] & 1;
			mode = 0;
		} else {
			if (toupper(string[0]) == 'I') {
				mode = 'I';
			} else if (toupper(string[0]) == 'O') {
				mode = 'O';
			} else if (toupper(string[0]) == 'S') {
				mode = 'S';
			} else {
				printf("Invalid.\n");
			};
		};
	};
};

void* second(void*) {
	char str4num[8];
	bool press = false;
	bool ruleAdded = false;
	TCHAR command[MAX_PATH + 115];

	while (1) {
		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(letter2)) {
			if (Switch) {
				press = !press;
				while (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(letter2)) {
					Sleep(1);
				};
			} else {
				press = true;
			};
		} else if (!Switch) {
			press = false;
		};

		if (press && !ruleAdded) {
			strcpy(command, "netsh advfirewall firewall set rule name=\"!BlockO ");

			sprintf(str4num, "%d", PID);
			strcat(command, str4num);
			strcat(command, "\" new enable=yes");
			system(command);
			Beep(0x650, 300);
			ruleAdded = true;
		} else if (!press && ruleAdded) {
			strcpy(command, "netsh advfirewall firewall set rule name=\"!BlockO ");
			strcat(command, str4num);
			strcat(command, "\" new enable=no");
			system(command);
			Beep(0x350, 300);
			ruleAdded = false;
		};
		Sleep(5);
	};
};