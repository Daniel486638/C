#include <windows.h>
#include <tlhelp32.h>

DWORD TERMINATEEVERTHING(char);

int main() {
	HWND Window = GetConsoleWindow();
	ShowWindow(Window, SW_HIDE);

	while (1) {
		if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(0x51) && GetAsyncKeyState(0x45)) {
			char L;
			while (GetAsyncKeyState(VK_LCONTROL) && (GetAsyncKeyState(0x51) || GetAsyncKeyState(0x45) || (!L || GetAsyncKeyState(0x4C)))) {
				if (!L) {
					L = GetAsyncKeyState(0x4C);
				};
				Sleep(1);
			};

			TERMINATEEVERTHING(0);
			if (L) {
				TERMINATEEVERTHING(1);
			};
		};

		Sleep(1);
	};
	

	return 0;
};

DWORD TERMINATEEVERTHING(char TERMYSELF) {
    PROCESSENTRY32 Entry;
    Entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	DWORD SPID = GetCurrentProcessId();

    if (Process32First(Snapshot, &Entry)) {
        do {
			DWORD PID = Entry.th32ProcessID;
			if (!TERMYSELF && PID != SPID) {
				TerminateProcess(OpenProcess(PROCESS_TERMINATE, 0, PID), 0);
			};
        } while (Process32Next(Snapshot, &Entry));
    };

    CloseHandle(Snapshot);

    return 0;
};