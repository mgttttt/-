#include <windows.h>
#include <commctrl.h>
#include <iostream>
#include <string.h>
#include <stdio.h>

#define ID_QUIT 1001
#define ID_TEXT 1002
#define ID_EDIT 1003
#define ID_GEN 1004
#define OnMenu3Clicked 1006
#define ON_COPY 1007
#define ON_PASTE 1008
#define ON_CUT 1009
#define ON_SAVE 1010


unsigned long buffer[1024];
long count = 0;

HWND edit, hwnd;
HWND g_hMainWindow = NULL;

void Generate(POINT point)
{
    char res[1024];
    int c = 0;
    if (count)
    {
        for (int i = 0; i < count; i++)
        {
            char temp = (point.x * buffer[i]) % 120 + 40;
            res[c++] = temp;
            temp = (point.y * buffer[i]) % 120 + 40;
            res[c++] = temp;
            if (i == 5) break;
        }
        if (count < 5)
        {
            char temp = (point.x * point.y) % 120 + 40;
            res[c++] = temp;
            temp = (point.y / point.x) % 120 + 40;
            res[c++] = temp;
            temp = (point.x / point.y) % 120 + 40;
            res[c++] = temp;
            temp = (abs(point.y - point.x)) % 120 + 40;
            res[c++] = temp;
            temp = (point.x + point.y) % 120 + 40;
            res[c++] = temp;
            temp = (point.y * point.y) % 120 + 40;
            res[c++] = temp;
            temp = (point.x * point.x) % 120 + 40;
            res[c++] = temp;
            temp = (point.y) % 120 + 40;
            res[c++] = temp;
            temp = (point.x) % 120 + 40;
            res[c++] = temp;
            temp = (point.y * point.x * point.x) % 120 + 40;
            res[c++] = temp;
        }
    }
    else
    {
        char temp = (point.x * point.y) % 120 + 40;
        res[c++] = temp;
        temp = (point.y / point.x) % 120 + 40;
        res[c++] = temp;
        temp = (point.x / point.y) % 120 + 40;
        res[c++] = temp;
        temp = (abs(point.y - point.x)) % 120 + 40;
        res[c++] = temp;
        temp = (point.x + point.y) % 120 + 40;
        res[c++] = temp;
        temp = (point.y * point.y) % 120 + 40;
        res[c++] = temp;
        temp = (point.x * point.x) % 120 + 40;
        res[c++] = temp;
        temp = (point.y) % 120 + 60;
        res[c++] = temp;
        temp = (point.x) % 120 + 40;
        res[c++] = temp;
        temp = (point.y * point.x * point.x) % 120 + 40;
        res[c++] = temp;
    }
    res[c] = '\0';
    SetWindowText(edit, res);
}

LRESULT CALLBACK LLKeyProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        DWORD vk = ((LPKBDLLHOOKSTRUCT)lParam)->vkCode;
        buffer[count] = vk;
        count++;
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
        edit = CreateWindowW(L"Edit", L"",
            WS_CHILD | WS_VISIBLE  | ES_AUTOVSCROLL,
            15, 15, 300, 200, hwnd, (HMENU)ID_EDIT, NULL, NULL);
        CreateWindowW(L"Button", L"Выйти", WS_VISIBLE | WS_CHILD, 220, 250, 80, 25, hwnd,
            (HMENU)ID_QUIT, NULL, NULL);
        CreateWindowW(L"Button", L"Сгенерировать пароль", WS_VISIBLE | WS_CHILD, 20, 250, 180, 25, hwnd,
            (HMENU)ID_GEN, NULL, NULL);
        break;
    case WM_COMMAND:
        switch (wParam)
        {
        case OnMenu3Clicked:
            MessageBox(hwnd, "Генератор паролей\nРазработчик: Тимура Данила", "О программе", MB_OK);
            break;
        case ON_CUT:
            SendDlgItemMessage(hwnd, ID_EDIT, WM_CUT, 0, 0);
            break;
        case ON_COPY:
            SendDlgItemMessage(hwnd, ID_EDIT, WM_COPY, 0, 0);
            break;
        case ON_PASTE:
            SendDlgItemMessage(hwnd, ID_EDIT, WM_PASTE, 0, 0);
            break;
        default:
            break;
        }
        switch (LOWORD(wParam))
        {
        case ID_TEXT:;
            char buff[1024];
            GetWindowText(edit, buff, 1024);
            MessageBox(NULL, buff, "Info!", MB_ICONINFORMATION | MB_OK);
            break;
        case ID_QUIT:
            PostQuitMessage(0);
            break;
        case ID_GEN:
            POINT point;
            GetCursorPos(&point);
            Generate(point);
            break;
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "myWindowClass";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    hwnd =
        CreateWindowEx(WS_EX_CLIENTEDGE, "myWindowClass", "Генератор паролей", WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, 350, 350, NULL, NULL, hInstance, NULL);
    if (hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG Msg;
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, LLKeyProc, GetModuleHandle(NULL), 0);
    if (hook)
    {
        while (WaitMessage())
        {
            Msg = { 0 };
            while (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
            {
                if (Msg.message == WM_QUIT)
                {
                    UnhookWindowsHookEx(hook);
                    return 0;
                }
                TranslateMessage(&Msg);
                DispatchMessage(&Msg);
            }
        }
    }
    return Msg.wParam;
}
