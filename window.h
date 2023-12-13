#pragma once
#pragma startup
#include <iostream>
#include <Windows.h>

#define ex1 exFunc1W(wp, size, pos, hi, title)
#define ex2 exFunc2W(wp, hi, icon)
#define ex3 exFunc3W(hwnd, wp, size, pos, hi, title, nshowcmd, msg)

#define ICON_ERROR IDI_ERROR
#define ICON_WARNING IDI_WARNING
#define ICON_INFO IDI_INFORMATION
#define ICON_DEFAULT IDI_APPLICATION
#define ICON_SHIELD IDI_SHIELD
#define ICON_NONE NULL

typedef LPWSTR ICON;


#define defaultPosW CW_USEDEFAULT
#define defaultPos (short)defaultPosW

HWND exFunc1W(WNDCLASSEX wp, COORD size, COORD pos, HINSTANCE hi, std::string title) {
    std::wstring wtitle(title.begin(), title.end());
    LPCWSTR lpctitle = (L"" + wtitle).c_str();
    HWND hwnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        wp.lpszClassName,
        lpctitle,
        WS_OVERLAPPEDWINDOW,
        pos.X,
        pos.Y,
        size.X,
        size.Y,
        NULL,
        NULL,
        hi,
        NULL
    );
    return hwnd;
}

LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wpa, LPARAM lpa) {
    switch (msg) {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wpa, lpa);
    }
}

void exFunc2W(WNDCLASSEX& wp, HINSTANCE hi, ICON icon) {
    wp.cbClsExtra = 0;
    wp.cbSize = sizeof(WNDCLASSEX);
    wp.cbWndExtra = 0;
    wp.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wp.hCursor = LoadCursor(hi, IDC_IBEAM);
    wp.hIcon = LoadIcon(hi, (LPCWSTR)icon); // IDI
    wp.hIconSm = wp.hIcon;
    wp.hInstance = hi;
    wp.lpfnWndProc = WindowProc;
    wp.lpszClassName = L"window";
    wp.lpszMenuName = NULL;
    wp.style = CS_HREDRAW | CS_VREDRAW;
}

void exFunc3W(HWND hwnd, WNDCLASSEX wp, COORD size, COORD pos, HINSTANCE hi, std::string title, int nshowcmd, MSG msg) {
    if (hwnd) {
        ShowWindow(hwnd, nshowcmd);
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    else {
        int clickedButton = MessageBoxW(NULL, L"window could not be created", L"bruh 💀", MB_ICONSTOP | MB_RETRYCANCEL);
        if (clickedButton == IDRETRY) {
            hwnd = ex1;
            if (hwnd) {
                ShowWindow(hwnd, nshowcmd);
                while (GetMessage(&msg, NULL, 0, 0)) {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
            else {
                MessageBoxW(NULL, L"still could not create window", L"crazy 🤑", MB_ICONWARNING | MB_OK);
            }
        }
    }
    return;
}

int newWindow(std::string title, ICON icon, COORD size, COORD pos) {
    HINSTANCE hi{ 0 }; // hinstance
    HINSTANCE hp{ 0 }; //hinstance previous
    LPSTR lpcmdl = NULL;
    int nshowcmd = SW_SHOWNORMAL;
    WNDCLASSEX wp;
    HWND hwnd;
    MSG msg{ 0 };
    ex2;
    ATOM regCl = RegisterClassEx(&wp);
    if (regCl) {
        hwnd = ex1;
        ex3;
    }
    else {
        int clickedButton = MessageBoxW(NULL, L"something went wrong lol", L"rip 😋😋", MB_ICONSTOP | MB_RETRYCANCEL);
        if (clickedButton == IDRETRY) {
            ex2;
            ATOM regCl = RegisterClassEx(&wp);
            if (regCl) {
                hwnd = ex1;
                ex3;
            }
            else {
                MessageBoxW(NULL, L"oh well, at least u tried", L"lmao 😭😭", MB_ICONWARNING | MB_OK);
                return 1;
            }
        }
        else {
            return 1;
        }
    }
}