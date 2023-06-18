#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <string.h>
#include <ShObjIdl.h>
#pragma warning(disable : 4996)

using namespace std;
NOTIFYICONDATA Icon = { 0 }; // Атрибуты значка
struct TodoItem {
    char text[256];
    bool done;
};

vector<TodoItem> items;
HWND edit1, edit2, edit3, edit4, hwnd;

void SaveList() {
    ofstream fout("C:\\1\\todo.txt");
    for (TodoItem item : items) {
        fout << item.text << endl;
    }
    fout.close();
}

void LoadList() {
    ifstream fin("C:\\1\\todo.txt");
    string line;
    while (getline(fin, line)) {
        TodoItem item;
        strcpy(item.text, line.c_str());
        item.done = false;
        items.push_back(item);
        SendMessage(edit3, LB_ADDSTRING, 0, (LPARAM)item.text);
    }
    fin.close();
}

void ShowNotification(string text, int timeout) {
    FLASHWINFO fwi;
    fwi.cbSize = sizeof(fwi);
    fwi.hwnd = hwnd;
    fwi.dwFlags = FLASHW_TRAY;
    fwi.uCount = timeout;
    fwi.dwTimeout = 0;
    FlashWindowEx(&fwi);

    NOTIFYICONDATA nid;
    nid.cbSize = sizeof(nid);
    nid.hWnd = hwnd;
    nid.uID = 1;
    nid.uFlags = NIF_INFO;
    nid.dwInfoFlags = NIIF_INFO;
    strcpy_s(nid.szInfo, text.c_str());
    nid.uTimeout = timeout * 1000;
    Shell_NotifyIcon(NIM_MODIFY, &nid);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        edit1 = CreateWindow("BUTTON", "Добавить", WS_CHILD | WS_VISIBLE, 10, 10, 100, 30, hwnd, (HMENU)1, NULL, NULL);
        edit2 = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 50, 400, 30, hwnd, (HMENU)2, NULL, NULL);
        edit3 = CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | WS_VSCROLL | WS_HSCROLL, 10, 100, 400, 100, hwnd, (HMENU)3, NULL, NULL);
        edit4 = CreateWindow("BUTTON", "Удалить", WS_CHILD | WS_VISIBLE, 120, 10, 100, 30, hwnd, (HMENU)4, NULL, NULL);
        break;
    }
    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case 1: {  
            ShowNotification("You have pending tasks!", 5);
            char text[256];
            GetWindowText(edit2, text, 256);
            TodoItem item;
            strcpy(item.text, text);
            item.done = false;
            items.push_back(item);
            SendMessage(edit3, LB_ADDSTRING, 0, (LPARAM)text);
            SetWindowText(edit2, "");
            break;
        }
        case 4: {
            DWORD dwSel = SendMessage(edit3, LB_GETCURSEL, 0, 0);

            if (dwSel > 0)
            {
                std::wstring str;
                SendMessage(edit3, LB_GETTEXT, dwSel, (LPARAM)str.c_str());
                SendMessage(edit3, LB_DELETESTRING, dwSel, 0);
                items.erase(items.begin() + dwSel);
            }
            break;
        }
        }
        break;
    }
    case WM_CLOSE:
        SaveList();
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        SaveList();
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
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
    wc.lpszClassName = "MainWindow";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Error registering window class!", "Error!", MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindowEx(
        0,
        "MainWindow",
        "TODO List",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 300,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, nCmdShow);
    LoadList();
    SetTimer(hwnd, 0, 5000, NULL);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        switch (msg.message) {
        case WM_TIMER:
            IUserNotification* un = NULL;
            if (CoCreateInstance(CLSID_UserNotification, 0, CLSCTX_ALL, IID_IUserNotification, (void**)&un) == S_OK)
            {
                un->SetBalloonInfo(L"TODO лист", L"Делайте дела", NIIF_INFO);
                un->Show(NULL, 0);
                un->Release();
            }
            break;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    SaveList();
    return msg.wParam;
}
