#include <stdio.h>
#include <windows.h>
#include <string.h>

int main() {
	HWND Window = GetConsoleWindow();
	ShowWindow(Window, SW_HIDE);
	char *UserName;
	char String1[] = "Hello, ";
	DWORD Length = 18;
	GetUserNameA(UserName, &Length);
	
	strcat(String1, UserName);
	strcat(String1, "!");
	MessageBox(NULL, String1, "Test", MB_OK);

	return 0;
}