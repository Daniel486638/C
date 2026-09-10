#include <windows.h>
#include <iostream>

void keyPress(WORD keyCode)
{
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = keyCode;
    input.ki.dwFlags = KEYEVENTF_SCANCODE;

    SendInput(1, &input, sizeof(INPUT));
};

//Your hook procedure
/*
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
        if (p->vkCode == 'D' && GetAsyncKeyState('F') >= 0) {
            if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
                // Suppress 'S' key
                return 1;
            }
        }; else if (p->vkCode == 'G') {
			if ((wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) && isPressed) {
                keyPress(0x1F);
				isPressed = 0;
            }
		};
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
*/
/*
int isStopped = 0;
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
        if (p->vkCode == 'S' && GetAsyncKeyState('G') >= 0) {
            if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
                // Suppress 'S' key
				isStopped = 1;
                return 1;
            }
        } else if (p->vkCode == 'G') {
			if ((wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)/* && isStopped*//*) {
                keyPress(0x1F);
				isStopped = 0;
            }
		};
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}*/

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
        if (p->vkCode == 'D' && GetAsyncKeyState('F') >= 0) {
            if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
                // Suppress 'D' key
                return 1;
            }
        } else if (p->vkCode == 'D' && GetAsyncKeyState('F') < 0) {
			if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
				return 1;
			};
		};
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    // Step 1: Set the hook
    HHOOK hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
    if (hHook == NULL) {
        std::cerr << "Failed to install hook!" << std::endl;
        return 1;
    }
    std::cout << "Hook installed. Press ESC to quit." << std::endl;

    // Step 2: Enter message loop to keep the hook active
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE) {
            //break;  // Exit on ESC key
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Step 3: Unhook when done
    UnhookWindowsHookEx(hHook);
    return 0;
}