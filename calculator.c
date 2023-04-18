#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#pragma warning(disable : 4996)

#define ID_EDIT1 1003
#define ID_0 1004
#define ID_1 1005
#define ID_2 1006
#define ID_3 1007
#define ID_4 1008
#define ID_5 1009
#define ID_6 1010
#define ID_7 1011
#define ID_8 1012
#define ID_9 1013
#define ID_A 1014
#define ID_B 1015
#define ID_C 1016
#define ID_D 1017
#define ID_E 1018
#define ID_F 1019
#define ID_MUL 1020
#define ID_SUB 1021
#define ID_ADD 1022
#define ID_CH 1023
#define ID_POINT 1024
#define ID_EQUAL 1025
#define ID_AND 1026
#define ID_OR 1027
#define ID_XOR 1028
#define ID_NOT 1029
#define ID_HEX 1030
#define ID_BIN 1031
#define ID_OCT 1032
#define ID_DEC 1033
#define ID_CT 1034
#define ID_BACSP 1035
#define ID_DIV 1036
#define ID_PER 1037
#define ID_SHIFTL 1038
#define ID_SHIFTR 1039
#define ID_EDIT2 1042
#define ID_EDIT3 1043
#define ID_EDIT4 1044
#define ID_EDIT5 1045

int hex = 0, dec = 0, oct = 0, bin = 0;
int j = 90;
long long temp = 0;
char temp_oper = 1;
int flag = 0;
int param = 2;
char* buff = (char*)malloc(sizeof(char) * 1024);

const char g_szClassName[] = "myWindowClass";
HWND edit1, edit2, edit3, edit4, edit5, button1, button2, button3, button4, button5, button6, button7, button8, button9, button10, button11, button12, button13, button14, button15, button16, button17, button18, button19, button20, button21, button22, button23, button24, button25, button26, button27, button28, button29, button30, button31, button32, button33, button34, button35, button36, button37, button38;

char* dvoich(long long x1)
{
    char buff[1024];
    int i, b;
    long long c = 0;
    for (i = 0; x1 > 0; i++)
    {
        b = x1 % 2;
        x1 = (x1 - b) / 2;
        c += b * pow(10, i);
    }
    sprintf(buff, "%lld", c);
    return buff;
}

void output()
{
    char buff[1024];
    sprintf(buff, "%X", temp);
    SetWindowText(edit4, buff);
    sprintf(buff, "%o", temp);
    SetWindowText(edit2, buff);
    sprintf(buff, "%lld", temp);
    SetWindowText(edit3, buff);
    sprintf(buff, "%s", dvoich(temp));
    SetWindowText(edit1, buff);
}

void Set_temp(int param)
{
    if (param == 1)
        temp_oper = 100;
    else if (param == 2)
        temp_oper = 101;
    else if (param == 3)
        temp_oper = 103;
    else if (param == 4)
        temp_oper = 104;
    else if (param == 5)
        temp_oper = 105;
    else if (param == 6)
        temp_oper = 106;
    else if (param == 7)
        temp_oper = 107;
    else if (param == 8)
        temp_oper = 108;
    else if (param == 9)
        temp_oper = 109;
    else if (param == 10)
        temp_oper = 110;
    else if (param == 11)
        temp_oper = 111;
    else if (param == 12)
        temp_oper = 112;
}

void Do_calc(HWND hwnd, int param)
{
    char *buff = (char *)malloc(sizeof(char) * 1024);
    if (temp_oper == 1)
    {
        GetWindowText(edit5, buff, 500);
        if (hex)
        {
            temp = strtol(buff, NULL, 16);
            sprintf(buff, "%X", temp);
        }
        else if (dec)
        {
            temp = atol(buff);
            sprintf(buff, "%lld", temp);
        }
        else if (oct)
        {
            temp = strtol(buff, NULL, 8);
            sprintf(buff, "%o", temp);
        }
        else
        {
            temp = strtol(buff, NULL, 2);
            buff = dvoich(temp);
        }
        Set_temp(param);
        if (param != 1000 && param != 112) SetWindowText(edit5, "");
        return;
    }
    if (temp_oper == 101)
    {
        GetWindowText(edit5, buff, 500);
        if (hex)
        {
            temp = temp - strtol(buff, NULL, 16);
            sprintf(buff, "%X", temp);
        }
        else if (dec)
        {
            temp = temp - atol(buff);
            sprintf(buff, "%lld", temp);
        }
        else if (oct)
        {
            temp = temp - strtol(buff, NULL, 8);
            sprintf(buff, "%o", temp);
        }
        else
        {
            temp = temp - strtol(buff, NULL, 2);
            buff = dvoich(temp);
        }
        Set_temp(param);
        if (param != 1000) SetWindowText(edit5, "");
        return;
    }
    if (temp_oper == 100)
    {
        GetWindowText(edit5, buff, 500);
        if (hex)
        {
            temp = temp + strtol(buff, NULL, 16);
            sprintf(buff, "%X", temp);
        }
        else if (dec)
        {
            temp = temp + atol(buff);
            sprintf(buff, "%lld", temp);
        }
        else if (oct)
        {
            temp = temp + strtol(buff, NULL, 8);
            sprintf(buff, "%o", temp);
        }
        else
        {
            temp += strtol(buff, NULL, 2);
            buff = dvoich(temp);
        }
        Set_temp(param);
        if (param != 1000) SetWindowText(edit5, "");
        return;
    }
    if (temp_oper == 103)
    {
        GetWindowText(edit5, buff, 500);
        if (hex)
        {
            temp = temp * strtol(buff, NULL, 16);
            sprintf(buff, "%X", temp);
        }
        else if (dec)
        {
            temp = temp * atol(buff);
            sprintf(buff, "%lld", temp);
        }
        else if (oct)
        {
            temp = temp * strtol(buff, NULL, 8);
            sprintf(buff, "%o", temp);
        }
        else
        {
            temp *= strtol(buff, NULL, 2);
            buff = dvoich(temp);
        }
        Set_temp(param);
        if (param != 1000) SetWindowText(edit5, "");
        return;
    }
    if (temp_oper == 104)
    {
        GetWindowText(edit5, buff, 500);
        if (hex)
        {
            temp = temp % strtol(buff, NULL, 16);
            sprintf(buff, "%X", temp);
        }
        else if (dec)
        {
            temp = temp % atol(buff);
            sprintf(buff, "%lld", temp);
        }
        else if (oct)
        {
            temp = temp % strtol(buff, NULL, 8);
            sprintf(buff, "%o", temp);
        }
        else
        {
            temp %= strtol(buff, NULL, 2);
            buff = dvoich(temp);
        }
        Set_temp(param);
        if (param != 1000) SetWindowText(edit5, "");
        return;
    }
    if (temp_oper == 105)
    {
        GetWindowText(edit5, buff, 500);
        if (hex)
        {
            temp = temp & strtol(buff, NULL, 16);
            sprintf(buff, "%X", temp);
        }
        else if (dec)
        {
            temp = temp & atol(buff);
            sprintf(buff, "%lld", temp);
        }
        else if (oct)
        {
            temp = temp & strtol(buff, NULL, 8);
            sprintf(buff, "%o", temp);
        }
        else
        {
            temp &= strtol(buff, NULL, 2);
            buff = dvoich(temp);
        }
        Set_temp(param);
        if (param != 1000) SetWindowText(edit5, "");
        return;
    }
    if (temp_oper == 106)
    {
        GetWindowText(edit5, buff, 500);
        if (hex)
        {
            temp = temp | strtol(buff, NULL, 16);
            sprintf(buff, "%X", temp);
        }
        else if (dec)
        {
            temp = temp | atol(buff);
            sprintf(buff, "%lld", temp);
        }
        else if (oct)
        {
            temp = temp | strtol(buff, NULL, 8);
            sprintf(buff, "%o", temp);
        }
        else
        {
            temp |= strtol(buff, NULL, 2);
            buff = dvoich(temp);
        }
        Set_temp(param);
        if (param != 1000) SetWindowText(edit5, "");
        return;
    }
    if (temp_oper == 107)
    {
        GetWindowText(edit5, buff, 500);
        if (hex)
        {
            temp = strtol(buff, NULL, 16);
            temp = ~temp;
            sprintf(buff, "%X", temp);
        }
        else if (dec)
        {
            temp = atol(buff);
            temp = ~temp;
            sprintf(buff, "%ll", temp);
        }
        else if (oct)
        {
            temp = strtol(buff, NULL, 8);
            temp = ~temp;
            sprintf(buff, "%o", temp);
        }
        else
        {
            temp = strtol(buff, NULL, 2);
            temp = ~temp;
            buff = dvoich(temp);
        }
        Set_temp(param);
        temp_oper = 1;
        if (param != 1000) SetWindowText(edit5, buff);
        return;
    }
    if (temp_oper == 108)
    {
        GetWindowText(edit5, buff, 500);
        if (hex)
        {
            temp = temp ^ strtol(buff, NULL, 16);
            sprintf(buff, "%X", temp);
        }
        else if (dec)
        {
            temp = temp ^ atol(buff);
            sprintf(buff, "%lld", temp);
        }
        else if (oct)
        {
            temp = temp ^ strtol(buff, NULL, 8);
            sprintf(buff, "%o", temp);
        }
        else
        {
            temp ^= strtol(buff, NULL, 2);
            buff = dvoich(temp);
        }
        Set_temp(param);
        if (param != 1000) SetWindowText(edit5, "");
        return;
    }
    if (temp_oper == 109)
    {
        GetWindowText(edit5, buff, 500);
        if (hex)
        {
            temp = temp / strtol(buff, NULL, 16);
            sprintf(buff, "%X", temp);
        }
        else if (dec)
        {
            temp = temp / atol(buff);
            sprintf(buff, "%lld", temp);
        }
        else if (oct)
        {
            temp = temp / strtol(buff, NULL, 8);
            sprintf(buff, "%o", temp);
        }
        else
        {
            temp /= strtol(buff, NULL, 2);
            buff = dvoich(temp);
        }
        Set_temp(param);
        if (param != 1000) SetWindowText(edit5, "");
        return;
    }
    if (temp_oper == 110)
    {
        GetWindowText(edit5, buff, 500);
        if (hex)
        {
            temp = strtol(buff, NULL, 16);
            //temp = temp << 1 | temp >> (16 - 1);
            temp *= 2;
            sprintf(buff, "%X", temp);
        }
        else if (dec)
        {
            temp = atol(buff);
            //temp = temp << 1 | temp >> (16 - 1);
            temp *= 2;
            sprintf(buff, "%lld", temp);
        }
        else if (oct)
        {
            temp = strtol(buff, NULL, 8);
            //temp = temp << 1 | temp >> (16 - 1);
            temp *= 2;
            sprintf(buff, "%o", temp);
        }
        else
        {
            temp = strtol(buff, NULL, 2);
            //temp = temp << 1 | temp >> (16 - 1);
            temp *= 2;
            buff = dvoich(temp);
        }
        Set_temp(param);
        temp_oper = 1;
        if (param != 1000) SetWindowText(edit5, buff);
        return;
    }
    if (temp_oper == 111)
    {
        GetWindowText(edit5, buff, 500);
        if (hex)
        {
            temp = strtol(buff, NULL, 16);
            //temp = temp >> 1 | temp << (16 - 1);
            temp /= 2;
            sprintf(buff, "%X", temp);
        }
        else if (dec)
        {
            temp = atol(buff);
            //temp = temp >> 1 | temp << (16 - 1);
            temp /= 2;
            sprintf(buff, "-%ud", temp);
        }
        else if (oct)
        {
            temp = strtol(buff, NULL, 8);
            //temp = temp >> 1 | temp << (16 - 1);
            temp /= 2;
            sprintf(buff, "%o", temp);
        }
        else
        {
            temp = strtol(buff, NULL, 2);
            //temp = temp >> 1 | temp << (16 - 1);
            temp /= 2;
            if (temp == 0) temp = 65536;
            char temp_buff[1024];
            //sprintf(temp_buff, );
            sprintf(buff, "-%s", dvoich(temp));
        }
        Set_temp(param);
        temp_oper = 1;
        if (param != 1000) SetWindowText(edit5, buff);
        return;
    }
    if (temp_oper == 112)
    {
        GetWindowText(edit5, buff, 500);
        if (hex)
        {
            temp = strtol(buff, NULL, 16);
            temp = -temp;
            sprintf(buff, "%X", temp);
        }
        else if (dec)
        {
            temp = atol(buff);
            temp = -temp;
            sprintf(buff, "%lld", temp);
        }
        else if (oct)
        {
            temp = strtol(buff, NULL, 8);
            temp = -temp;
            sprintf(buff, "%o", temp);
        }
        else
        {
            temp = strtol(buff, NULL, 2);
            temp = -temp;
            buff = dvoich(temp);
        }
        Set_temp(param);
        temp_oper = 1;
        if (param != 1000) SetWindowText(edit5, buff);
        return;
    }
}

void Add_text(const char * buff) {
    if (flag) { SetWindowText(edit5, ""); flag = 0; }
    SendMessage(edit5, EM_SETSEL, 0, -1);
    SendMessage(edit5, EM_SETSEL, -1, 0);
    SendMessage(edit5, EM_REPLACESEL, 0, (LPARAM)buff);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
        edit1 = CreateWindowW(L"Edit", L"",
            WS_CHILD | WS_VISIBLE, 70, 60 + j, 400, 25, hwnd, (HMENU)ID_EDIT1, NULL, NULL);
        edit2 = CreateWindowW(L"Edit", L"",
            WS_CHILD | WS_VISIBLE, 70, 25 + j, 400, 25, hwnd, (HMENU)ID_EDIT2, NULL, NULL);
        edit3 = CreateWindowW(L"Edit", L"",
            WS_CHILD | WS_VISIBLE, 70, -10 + j, 400, 25, hwnd, (HMENU)ID_EDIT3, NULL, NULL);
        edit4 = CreateWindowW(L"Edit", L"",
            WS_CHILD | WS_VISIBLE, 70, -45 + j, 400, 25, hwnd, (HMENU)ID_EDIT4, NULL, NULL);
        edit5 = CreateWindowW(L"Edit", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER, 10, -80 + j, 440, 25, hwnd, (HMENU)ID_EDIT5, NULL, NULL);
        button1 = CreateWindowW(L"Button", L"0", WS_VISIBLE | WS_CHILD, 190, 305 + j, 80, 25, hwnd,
            (HMENU)ID_0, NULL, NULL);
        button2 = CreateWindowW(L"Button", L"1", WS_VISIBLE | WS_CHILD, 100, 270 + j, 80, 25, hwnd,
            (HMENU)ID_1, NULL, NULL);
        button3 = CreateWindowW(L"Button", L"2", WS_VISIBLE | WS_CHILD, 190, 270 + j, 80, 25, hwnd,
            (HMENU)ID_2, NULL, NULL);
        button4 = CreateWindowW(L"Button", L"3", WS_VISIBLE | WS_CHILD, 280, 270 + j, 80, 25, hwnd,
            (HMENU)ID_3, NULL, NULL);
        button5 = CreateWindowW(L"Button", L"4", WS_VISIBLE | WS_CHILD, 100, 235 + j, 80, 25, hwnd,
            (HMENU)ID_4, NULL, NULL);
        button6 = CreateWindowW(L"Button", L"5", WS_VISIBLE | WS_CHILD, 190, 235 + j, 80, 25, hwnd,
            (HMENU)ID_5, NULL, NULL);
        button7 = CreateWindowW(L"Button", L"6", WS_VISIBLE | WS_CHILD, 280, 235 + j, 80, 25, hwnd,
            (HMENU)ID_6, NULL, NULL);
        button8 = CreateWindowW(L"Button", L"7", WS_VISIBLE | WS_CHILD, 100, 200 + j, 80, 25, hwnd,
            (HMENU)ID_7, NULL, NULL);
        button9 = CreateWindowW(L"Button", L"8", WS_VISIBLE | WS_CHILD, 190, 200 + j, 80, 25, hwnd,
            (HMENU)ID_8, NULL, NULL);
        button10 = CreateWindowW(L"Button", L"9", WS_VISIBLE | WS_CHILD, 280, 200 + j, 80, 25, hwnd,
            (HMENU)ID_9, NULL, NULL);
        button11 = CreateWindowW(L"Button", L"A", WS_VISIBLE | WS_CHILD, 10, 130 + j, 80, 25, hwnd,
            (HMENU)ID_A, NULL, NULL);
        button12 = CreateWindowW(L"Button", L"B", WS_VISIBLE | WS_CHILD, 10, 165 + j, 80, 25, hwnd,
            (HMENU)ID_B, NULL, NULL);
        button13 = CreateWindowW(L"Button", L"C", WS_VISIBLE | WS_CHILD, 10, 200 + j, 80, 25, hwnd,
            (HMENU)ID_C, NULL, NULL);
        button14 = CreateWindowW(L"Button", L"D", WS_VISIBLE | WS_CHILD, 10, 235 + j, 80, 25, hwnd,
            (HMENU)ID_D, NULL, NULL);
        button15 = CreateWindowW(L"Button", L"E", WS_VISIBLE | WS_CHILD, 10, 270 + j, 80, 25, hwnd,
            (HMENU)ID_E, NULL, NULL);
        button16 = CreateWindowW(L"Button", L"F", WS_VISIBLE | WS_CHILD, 10, 305 + j, 80, 25, hwnd,
            (HMENU)ID_F, NULL, NULL);
        button17 = CreateWindowW(L"Button", L"X", WS_VISIBLE | WS_CHILD, 370, 200 + j, 80, 25, hwnd,
            (HMENU)ID_MUL, NULL, NULL);
        button18 = CreateWindowW(L"Button", L"-", WS_VISIBLE | WS_CHILD, 370, 235 + j, 80, 25, hwnd,
            (HMENU)ID_SUB, NULL, NULL);
        button19 = CreateWindowW(L"Button", L"+", WS_VISIBLE | WS_CHILD, 370, 270 + j, 80, 25, hwnd,
            (HMENU)ID_ADD, NULL, NULL);
        button20 = CreateWindowW(L"Button", L"+/-", WS_VISIBLE | WS_CHILD, 100, 305 + j, 80, 25, hwnd,
            (HMENU)ID_CH, NULL, NULL);
        button22 = CreateWindowW(L"Button", L"=", WS_VISIBLE | WS_CHILD, 370, 305 + j, 80, 25, hwnd,
            (HMENU)ID_EQUAL, NULL, NULL);
        button23 = CreateWindowW(L"Button", L"C", WS_VISIBLE | WS_CHILD, 280, 305 + j, 80, 25, hwnd,
            (HMENU)ID_CT, NULL, NULL);
        button25 = CreateWindowW(L"Button", L"%", WS_VISIBLE | WS_CHILD, 280, 165 + j, 80, 25, hwnd,
            (HMENU)ID_PER, NULL, NULL);
        button26 = CreateWindowW(L"Button", L"/", WS_VISIBLE | WS_CHILD, 370, 165 + j, 80, 25, hwnd,
            (HMENU)ID_DIV, NULL, NULL);
        button27 = CreateWindowW(L"Button", L"<<", WS_VISIBLE | WS_CHILD, 100, 165 + j, 80, 25, hwnd,
            (HMENU)ID_SHIFTL, NULL, NULL);
        button28 = CreateWindowW(L"Button", L">>", WS_VISIBLE | WS_CHILD, 190, 165 + j, 80, 25, hwnd,
            (HMENU)ID_SHIFTR, NULL, NULL);
        button31 = CreateWindowW(L"Button", L"AND", WS_VISIBLE | WS_CHILD, 100, 130 + j, 80, 25, hwnd,
            (HMENU)ID_AND, NULL, NULL);
        button32 = CreateWindowW(L"Button", L"OR", WS_VISIBLE | WS_CHILD, 190, 130 + j, 80, 25, hwnd,
            (HMENU)ID_OR, NULL, NULL);
        button33 = CreateWindowW(L"Button", L"NOT", WS_VISIBLE | WS_CHILD, 280, 130 + j, 80, 25, hwnd,
            (HMENU)ID_NOT, NULL, NULL);
        button34 = CreateWindowW(L"Button", L"XOR", WS_VISIBLE | WS_CHILD, 370, 130 + j, 80, 25, hwnd,
            (HMENU)ID_XOR, NULL, NULL);
        button35 = CreateWindowW(L"Button", L"HEX", WS_VISIBLE | WS_CHILD, 10, -45 + j, 50, 25, hwnd,
            (HMENU)ID_HEX, NULL, NULL);
        button36 = CreateWindowW(L"Button", L"DEC", WS_VISIBLE | WS_CHILD, 10, -10 + j, 50, 25, hwnd,
            (HMENU)ID_DEC, NULL, NULL);
        button37 = CreateWindowW(L"Button", L"OCT", WS_VISIBLE | WS_CHILD, 10, 25 + j, 50, 25, hwnd,
            (HMENU)ID_OCT, NULL, NULL);
        button38 = CreateWindowW(L"Button", L"BIN", WS_VISIBLE | WS_CHILD, 10, 60 + j, 50, 25, hwnd,
            (HMENU)ID_BIN, NULL, NULL);
        EnableWindow(button3, true); EnableWindow(button4, true); EnableWindow(button5, true); EnableWindow(button6, true);
        EnableWindow(button10, true); EnableWindow(button9, true); EnableWindow(button8, true); EnableWindow(button7, true);
        EnableWindow(button11, false); EnableWindow(button12, false); EnableWindow(button13, false); EnableWindow(button14, false);
        EnableWindow(button15, false); EnableWindow(button16, false);
        dec = 1;
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_BIN:
            EnableWindow(button3, false); EnableWindow(button4, false); EnableWindow(button5, false); EnableWindow(button6, false);
            EnableWindow(button10, false); EnableWindow(button9, false); EnableWindow(button8, false); EnableWindow(button7, false);
            EnableWindow(button11, false); EnableWindow(button12, false); EnableWindow(button13, false); EnableWindow(button14, false);
            EnableWindow(button15, false); EnableWindow(button16, false);
            bin = 1; oct = 0; dec = 0; hex = 0;
            break;
        case ID_OCT:
            EnableWindow(button3, true); EnableWindow(button4, true); EnableWindow(button5, true); EnableWindow(button6, true);
            EnableWindow(button10, false); EnableWindow(button9, false); EnableWindow(button8, true); EnableWindow(button7, true);
            EnableWindow(button11, false); EnableWindow(button12, false); EnableWindow(button13, false); EnableWindow(button14, false);
            EnableWindow(button15, false); EnableWindow(button16, false);
            bin = 0; oct = 1; dec = 0; hex = 0;
            break;
        case ID_DEC:
            EnableWindow(button3, true); EnableWindow(button4, true); EnableWindow(button5, true); EnableWindow(button6, true);
            EnableWindow(button10, true); EnableWindow(button9, true); EnableWindow(button8, true); EnableWindow(button7, true);
            EnableWindow(button11, false); EnableWindow(button12, false); EnableWindow(button13, false); EnableWindow(button14, false);
            EnableWindow(button15, false); EnableWindow(button16, false);
            bin = 0; oct = 0; dec = 1; hex = 0;
            break;
        case ID_HEX:
            EnableWindow(button3, true); EnableWindow(button4, true); EnableWindow(button5, true); EnableWindow(button6, true);
            EnableWindow(button10, true); EnableWindow(button9, true); EnableWindow(button8, true); EnableWindow(button7, true);
            EnableWindow(button11, true); EnableWindow(button12, true); EnableWindow(button13, true); EnableWindow(button14, true);
            EnableWindow(button15, true); EnableWindow(button16, true);
            bin = 0; oct = 0; dec = 0; hex = 1;
            break;
        case ID_0:
            Add_text("0");
            break;
        case ID_1:
            Add_text("1");
            break;
        case ID_2:
            Add_text("2");
            break;
        case ID_3:
            Add_text("3");
            break;
        case ID_4:
            Add_text("4");
            break;
        case ID_5:
            Add_text("5");
            break;
        case ID_6:
            Add_text("6");
            break;
        case ID_7:
            Add_text("7");
            break;
        case ID_8:
            Add_text("8");
            break;
        case ID_9:
            Add_text("9");
            break;
        case ID_A:
            Add_text("A");
            break;
        case ID_B:
            Add_text("B");
            break;
        case ID_C:
            Add_text("C");
            break;
        case ID_D:
            Add_text("D");
            break;
        case ID_E:
            Add_text("E");
            break;
        case ID_F:
            Add_text("F");
            break;
        case ID_ADD:
            Do_calc(hwnd, 1);
            break;
        case ID_SUB:
            Do_calc(hwnd, 2);
            break;
        case ID_MUL:
            Do_calc(hwnd, 3);
            break;
        case ID_PER:
            Do_calc(hwnd, 4);
            break;
        case ID_AND:
            Do_calc(hwnd, 5);
            break;
        case ID_OR:
            Do_calc(hwnd, 6);
            break;
        case ID_NOT:
            temp_oper = 107;
            Do_calc(hwnd, 7);
            break;
        case ID_XOR:
            Do_calc(hwnd, 8);
            break;
        case ID_DIV:
            Do_calc(hwnd, 9);
            break;
        case ID_SHIFTL:
            temp_oper = 110;
            Do_calc(hwnd, 10);
            break;
        case ID_SHIFTR:
            temp_oper = 111;
            Do_calc(hwnd, 11);
        case ID_CH:
            temp_oper = 112;
            Do_calc(hwnd, 12);
            break;
        case ID_EQUAL:
            flag = 1;
            Do_calc(hwnd, 1000);
            temp_oper = 1;
            char res[1024];
            if (hex)
                sprintf(res, "%X", temp);
            if (dec)
                sprintf(res, "%lld", temp);
            if (oct)
                sprintf(res, "%o", temp);
            if (bin)
            {
                sprintf(res, "%s", dvoich(temp));
            }
            output();
            SetWindowText(edit5, res);
            temp = 0;
            break;
        case ID_CT:
            flag = 0;
            temp = 0;
            temp_oper = 1;
            SetWindowText(edit5, "");
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
    HWND hwnd;
    hwnd =
        CreateWindowEx(WS_EX_CLIENTEDGE, "myWindowClass", "Hello from WinAPI!", WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, 480, 470, NULL, NULL, hInstance, NULL);
    if (hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG Msg;
    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
