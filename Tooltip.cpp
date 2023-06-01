#include "Tooltip.h"

Tooltip::Tooltip(const HWND& hwnd, const int& ID, const std::string& message) {
	this->hwnd = hwnd;
	this->ID = ID;
	this->message = message;
	this->create();
}

void Tooltip::create() {
    //get HWND of item the tooltip will be on.
    HWND hButton = GetDlgItem(hwnd, ID);

    //get access to the tooltip object.
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icex);

    //make the tooltip window.
    HWND hwndTT = CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL,
        WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, hwnd, NULL, GetModuleHandle(NULL), NULL);

    //make the tooltip itself, including size and text.
    TOOLINFO ti;
    ti.cbSize = sizeof(TOOLINFO);
    ti.uFlags = TTF_SUBCLASS | TTF_IDISHWND;
    ti.hwnd = hwnd;
    ti.uId = (UINT_PTR)hButton;
    ti.hinst = GetModuleHandle(NULL);
    const char* text = message.c_str();
    ti.lpszText = T2A(const_cast<char*>(text));;
    ti.rect = { 0 };

    //send the message with the tooltip to create it
    //in the GUI.
    SendMessage(hwndTT, TTM_ADDTOOL, 0, (LPARAM)&ti);
}

void initiate(HWND hwnd) {
    //make all the tooltips for the vulnerability form.
    Tooltip vulnButton(hwnd, IDC_NEWVULN, "Use all the code objects created since last click");
    Tooltip codeButton(hwnd, IDC_NEWCODE, "Create a code object using all code lines since last click and other parameters");
    Tooltip addCodeButton(hwnd, IDC_CODEBTN, "will add to the list of code lines that will be used to create next code object");
    Tooltip createButtom(hwnd, IDC_BUTTON, "Create the website with chosen and user-added vulnerabilities protected");
    Tooltip xssMore(hwnd, IDC_XSSMORE, "Learn more about the XSS vulnerability");
    Tooltip sqliMore(hwnd, IDC_SQLIMORE, "Learn more about the SQL Injection vulnerability");
    Tooltip redirectMore(hwnd, IDC_REDIRECTMORE, "Learn more about the Unvalidated Redirects vulnerability");
    Tooltip tamperMore(hwnd, IDC_TAMPERMORE, "Learn more about the Product Tampering vulnerability");
    Tooltip adminMore(hwnd, IDC_ADMINMORE, "Learn more about the Admin Registration vulnerability");
}

Tooltip::~Tooltip() {

}