#include <windows.h>
#include <stdio.h>

enum ButtonID {
    ID_BTN_ADD = 1,
    ID_BTN_SUB,
    ID_BTN_MUL, 
    ID_BTN_DIV 
};

HWND hEdit1, hEdit2;

void RunCalculation(HWND hwnd, int opType) {
    char buf1[100], buf2[100], resStr[100];
    double n1, n2, res = 0;

    GetWindowText(hEdit1, buf1, 100);
    GetWindowText(hEdit2, buf2, 100);

    n1 = atof(buf1);

    char *numStart = buf2;
    while (*numStart && !isdigit(*numStart) && *numStart != '-') {
        numStart++;
    }
    n2 = (*numStart) ? atof(numStart) : 0;

    char opChar;
    if (opType == ID_BTN_ADD) opChar = '+';
    else if (opType == ID_BTN_SUB) opChar = '-';
    else if (opType == ID_BTN_MUL) opChar = '*';
    else if (opType == ID_BTN_DIV) opChar = '/';

    char newEdit2[100];
    sprintf(newEdit2, "%c %g", opChar, n2); 
    SetWindowText(hEdit2, newEdit2);

    switch (opType) {
        case ID_BTN_ADD: res = n1 + n2; break;
        case ID_BTN_SUB: res = n1 - n2; break;
        case ID_BTN_MUL: res = n1 * n2; break;
        case ID_BTN_DIV: 
            if (n2 != 0) res = n1 / n2; 
            else { MessageBox(hwnd, "Cannot divide by zero!", "Result", MB_OK); return; }
            break;
    }

    sprintf(resStr, "%.6f", res); 
    MessageBox(hwnd, resStr, "Result", MB_OK);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch(Message) {
        case WM_CREATE: {
            CreateWindow("STATIC", "Please input two numbers", 
                WS_VISIBLE | WS_CHILD | SS_CENTER, 20, 20, 245, 20, hwnd, NULL, NULL, NULL);

            hEdit1 = CreateWindow("EDIT", "", 
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 40, 50, 205, 25, hwnd, NULL, NULL, NULL);

            hEdit2 = CreateWindow("EDIT", "", 
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 40, 85, 205, 25, hwnd, NULL, NULL, NULL);

            CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD, 60, 130, 35, 30, hwnd, (HMENU)ID_BTN_ADD, NULL, NULL);
            CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD, 105, 130, 35, 30, hwnd, (HMENU)ID_BTN_SUB, NULL, NULL);
            CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD, 150, 130, 35, 30, hwnd, (HMENU)ID_BTN_MUL, NULL, NULL);
            CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD, 195, 130, 35, 30, hwnd, (HMENU)ID_BTN_DIV, NULL, NULL);
            break;
        }

        case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            if (wmId >= 1 && wmId <= 4) {
                RunCalculation(hwnd, wmId);
            }
            break;
        }

        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    memset(&wc,0,sizeof(wc));
    wc.cbSize    = sizeof(WNDCLASSEX);
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.hCursor   = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszClassName = "WindowClass";
    wc.hIcon     = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm   = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 315, 220, NULL,NULL,hInstance,NULL);

    if(hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    while(GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}