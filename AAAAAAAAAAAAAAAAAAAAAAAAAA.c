#include <windows.h>

void keyPress(WORD keyCode)
{
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = keyCode;
    input.ki.dwFlags = KEYEVENTF_SCANCODE;

    SendInput(1, &input, sizeof(INPUT));
}

void keyRelease(WORD keyCode)
{
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = keyCode;
    input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;

    SendInput(1, &input, sizeof(INPUT));
}

int main()
{
    Sleep(5000); // pause time to open browser tab
    keyPress(0x11); // press key
    Sleep(10000); // hold key for x milliseconds
    keyRelease(0x11); // release key
    return 0;
}