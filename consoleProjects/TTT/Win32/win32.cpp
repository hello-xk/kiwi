// win32.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
using namespace std;

LRESULT CALLBACK LowLevelKeyboardProc(int code, WPARAM wParam, LPARAM lParam) {
    if (code == HC_ACTION) {
        switch (wParam) {
        case WM_KEYDOWN:
            PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
            char c = char(MapVirtualKey(p->vkCode, MAPVK_VK_TO_CHAR));
            cout << c << endl;
        }
    }
    return CallNextHookEx(NULL, code, wParam, lParam);
}

int _tmain(int argc, _TCHAR* argv[])
{
    HHOOK HKeyboard = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(0), GetCurrentThreadId());

    MSG msg;
    BOOL bRet;

    while ((bRet = GetMessage(&msg, NULL, 0, 0)) > 0) {
        cout << "bRet = " << bRet << endl; // I want to do something here, but the program doesn't seem to go in here
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(HKeyboard);

	return 0;
}

