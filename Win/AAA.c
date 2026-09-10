// Copyright (c) 2026 Марченко Даниил

#include <windows.h> // Required for Win32 API functions

void SendKey(WORD virtualKeyCode) {
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    //ip.ki.wScan = 0; // Hardware scan code for the key
    ip.ki.time = 1000;
    //ip.ki.dwExtraInfo = 0;

    // Press the key
    ip.ki.wVk = virtualKeyCode; // Virtual-key code for the key
   // ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
	Sleep(1000);

    // Release the key
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));
}

int main() {
    // Wait for 5 seconds to switch to another application, like Notepad
    Sleep(5000); 

    // Send the 'A' key
    //SendKey(0x41); // 0x41 is the virtual key code for 'A'
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0x20;
	//ip.ki.time = 0;
	//ip.ki.dwExtraInfo = 0;
	//ip.ki.wVk = 'W';
	ip.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));
	Sleep(10000);

    return 0;
}
