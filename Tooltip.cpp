#include "Tooltip.h"

Tooltip::Tooltip(const HWND hwnd, const int ID, const std::string message) {
	this->hwnd = hwnd;
	this->ID = ID;
	this->message = message;
	this->create();
}

void Tooltip::create() {
    HWND hButton = GetDlgItem(hwnd, ID);

    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icex);

    HWND hwndTT = CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL,
        WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, hwnd, NULL, GetModuleHandle(NULL), NULL);

    TOOLINFO ti;
    ti.cbSize = sizeof(TOOLINFO);
    ti.uFlags = TTF_SUBCLASS | TTF_IDISHWND;
    ti.hwnd = hwnd;
    ti.uId = (UINT_PTR)hButton;
    ti.hinst = GetModuleHandle(NULL);
    const char* text = message.c_str();
    ti.lpszText = T2A(const_cast<char*>(text));;
    ti.rect = { 0 };

    SendMessage(hwndTT, TTM_ADDTOOL, 0, (LPARAM)&ti);
}

Tooltip::~Tooltip() {

}