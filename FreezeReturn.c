#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

DWORD* ThreadF(DWORD, bool);
DWORD GetPID(char*);

int main(int ArgLength, char **Args) {
	HWND Window = GetConsoleWindow();
	printf("Program was created by Daniel486638.\n");//ShowWindow(Window, SW_HIDE);
	char String[] = "RobloxPlayerBeta";
	DWORD PID = GetPID(String);
	//sscanf(Args[1], "%d", &PID);
	while (1) {
		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(0x45)) {
			ThreadF(PID, true);
			while (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(0x45)) {
				Sleep(1);
			};
			ThreadF(PID, false);
		};
		Sleep(1);
	};

	return 0;
};

DWORD* ThreadF(DWORD PID, bool Suspend){
	THREADENTRY32 Entry;
	Entry.dwSize = sizeof(THREADENTRY32);
	HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	unsigned char i = 0;
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
		} while (Thread32Next(Snapshot, &Entry));
	};
	CloseHandle(Snapshot);
	return 0;
};


DWORD GetPID(char *TargetName) {
	TargetName = TargetName ? strcat(TargetName, ".exe") : TargetName;
    PROCESSENTRY32 Entry;
    Entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (Process32First(Snapshot, &Entry)) {
        do {
            if (TargetName == NULL) {
                printf("\n%s", Entry.szExeFile);
            } else if (!strcmp(TargetName, Entry.szExeFile)) {
                printf("Process name: %s\nPID: %i\n", TargetName, Entry.th32ProcessID);
                return Entry.th32ProcessID;
            };
        } while (Process32Next(Snapshot, &Entry));
    };
    CloseHandle(Snapshot);
    return 0;
};