#include <stdio.h>
#include <windows.h>

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define keyCode 'D'

int main() {
    while (1) {
        if (KEY_DOWN('F')) {
            keybd_event(keyCode, 0, 0, 0);
			while (KEY_DOWN('F')) {
				Sleep(1);
			};
			keybd_event(keyCode, 0, KEYEVENTF_KEYUP, 0);
        };
        // Add a small delay to avoid excessive CPU usage
        Sleep(1);
    }
    return 0;
}