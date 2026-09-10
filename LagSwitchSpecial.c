// -liphlpapi
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
#include <iphlpapi.h>
#include <stdio.h>

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
	IP_ADAPTER_INFO *info = NULL, *pos;
    DWORD size = 0;

    GetAdaptersInfo(info, &size);

    info = (IP_ADAPTER_INFO *)malloc(size);

    GetAdaptersInfo(info, &size);

	long long unsigned AAA = 0x88d7f67f9cb5;
	long long unsigned AAA2 = 0x0;

    for (pos=info; pos!=NULL; pos=pos->Next) {
        /*printf("\n%s\n\t", pos->Description);
        printf("%2.2x", pos->Address[0]);*/
		if (pos->Description[0] == 'R' && pos->Description[1] == 'e') {
			AAA2 = pos->Address[0];
			for (int i=1; i < pos->AddressLength; i++) {
				AAA2 = AAA2 << 8;
				AAA2 = AAA2 | pos->Address[i];
			}
		}
    }
	if (AAA != AAA2) {
		printf("Unauthorised.\n");
		getchar();
		return 1;
	};

    free(info);
	HWND Window = GetConsoleWindow();
	printf("Program was created by Daniel486638.\nSend 1 or 2 or S and then send your key for the hot key or change the mode (1 for switch and 0 for hold) respectively (for example, if you send 1 and then E, block will be activated by CTRL + E).\n");//ShowWindow(Window, SW_HIDE);
	DWORD PID;
	//sscanf(Args[1], "%d", &PID);
	pthread_t *TID = (pthread_t*)malloc(sizeof(pthread_t));
	pthread_create(TID, NULL, read, NULL);
	TCHAR filename[MAX_PATH];
	TCHAR command[MAX_PATH + 115];
	char str4num[8];
	bool press = false;
	bool ruleAdded = false;

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
			ruleAdded = true;
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
			Switch = string[0] & 1;
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