#include <windows.h>
#include <iostream>

DWORD ProcessID;

HWND hwndOutput; // Global variable for the output box, if u remove it its gonna be like the chernobyl security test, yknow what happened, right?

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            CreateWindowA("STATIC", "Window Name:", WS_VISIBLE | WS_CHILD | SS_LEFT, 10, 10, 100, 20, hwnd, NULL, NULL, NULL);

            CreateWindowA("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 120, 10, 170, 20, hwnd, (HMENU)1, NULL, NULL);

            hwndOutput = CreateWindowA("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL, 10, 40, 280, 100, hwnd, NULL, NULL, NULL);

            // create button (very important)
            CreateWindowA("BUTTON", "Detect Rune", WS_VISIBLE | WS_CHILD, 10, 150, 100, 30, hwnd, (HMENU)2, NULL, NULL);

            break;
        }
        case WM_COMMAND: {
            if (LOWORD(wParam) == 2) { // Use ID 2 for the button
                char windowName[256];
                GetWindowTextA(GetDlgItem(hwnd, 1), windowName, 256); // Use ID 1 for the edit control

                HWND hwndDetected = FindWindowA(NULL, windowName);

                if (hwndDetected) {
                    SendMessageA(hwndOutput, EM_SETSEL, -1, -1);
                    SendMessageA(hwndOutput, EM_REPLACESEL, 0, (LPARAM)"Rune found lmaoo\n");
                } else {
                    DWORD error = GetLastError();
                    std::cout << "Error code: " << error << std::endl;

                    SendMessageA(hwndOutput, EM_SETSEL, -1, -1);
                    SendMessageA(hwndOutput, EM_REPLACESEL, 0, (LPARAM)"RUNE UNDETECTED W PRINTSPLOIT");
                }
            }
            break;
        }
        case WM_ERASEBKGND: {
            HDC hdc = (HDC)wParam;
            RECT rect;
            GetClientRect(hwnd, &rect);
            FillRect(hdc, &rect, CreateSolidBrush(RGB(192, 192, 192))); // RGB values for grey
            return 1; // Tell Windows that we've handled erasing the background
        }
        case WM_CLOSE: {
            DestroyWindow(hwnd);
            break;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int main() {
    WNDCLASSA wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "MyWindowClass";
    wc.hbrBackground = CreateSolidBrush(RGB(192, 192, 192)); // bg color (bg= background)

    if (!RegisterClassA(&wc)) {
        MessageBoxA(NULL, "Error registering window class.", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    HWND hwnd = CreateWindowA("MyWindowClass", "Rune Detector", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 300, 250, 0, 0, 0, 0); //mywindowclass lmaoooo

    if (!hwnd) {
        MessageBoxA(NULL, "Error creating window.", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
