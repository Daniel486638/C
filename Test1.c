#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

DWORD GetPID(char*);
unsigned long GetBaseAddress(char*, DWORD);

int main(int ArgLength, char **Args) {
    DWORD PID;
    HANDLE Handle;
    char *TargetName = NULL;
    bool IsEmpty[] = {
        TargetName == NULL,
        TargetName == NULL
    };
	PID = GetPID(TargetName);
	getchar();
    if (IsEmpty[0]) {
        return 0;
    } else if (!PID) {
        printf("Process does not exist.");
        return 1;
    };
    
    if (!(Handle = OpenProcess(PROCESS_ALL_ACCESS, 0, PID))) {
        printf("No permission.");
        return 1;
    };
    
    printf("Handle: %i\n", Handle);

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

unsigned long GetBaseAddress(char *TargetName, DWORD PID) {
	MODULEENTRY32 Entry;
	Entry.dwSize = sizeof(MODULEENTRY32);
    HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);
    if (Module32First(Snapshot, &Entry)) {
        do {
            if (!strcmp(TargetName, "ls")) {
                printf("\n%s", Entry.szModule);
            } else if (!strcmp(TargetName, Entry.szModule)) {
                printf("Module name: %s\nBase address: %p", TargetName, Entry.modBaseAddr);
                CloseHandle(Snapshot);
                return (long long)Entry.modBaseAddr;
            };
        } while (Module32Next(Snapshot,&Entry));
    };
    CloseHandle(Snapshot);
    return 0;
};