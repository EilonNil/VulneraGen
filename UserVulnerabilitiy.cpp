#include "UserVulnerability.h"

std::string getEditString(HWND hwnd, int item) {
    HWND edit = GetDlgItem(hwnd, item);
    char buf[1024];
    GetWindowText(edit, buf, 1024);
    SetWindowText(edit, "");
    std::string line = buf;
    return line;
}

int getEditInt(HWND hwnd, int item) {
    std::string line = getEditString(hwnd, item);
    return atoi(line.c_str());
}//maybe use stoi and catch exception insead cuz 0 can be valid but not what was wanted?

Code getEditCode(HWND hwnd, std::vector<std::string> lines) {
    std::string filePath = getEditString(hwnd, IDC_PATH);
    int beginLine = getEditInt(hwnd, IDC_BEGINLINE);
    int beginChar = getEditInt(hwnd, IDC_BEGINCHAR);
    int endLine = getEditInt(hwnd, IDC_ENDLINE);
    int endChar = getEditInt(hwnd, IDC_ENDCHAR);
    Code code(filePath, beginLine, beginChar, endLine, endChar, lines);
    if (isCodeValid(code)) {
        return code;
    }
    return Code();
}

bool isCodeValid(Code code) {
    bool valid = true;
    if (!doesExist(code.getFilePath())) {
        valid = false;
        printError("File path is invalid. File does not exist");
    }
    if (code.beginLine <= 0) {
        valid = false;
        printError("Begin line cannot be smaller than or equal to 0");
    }
    if (code.endLine <= 0) {
        valid = false;
        printError("End line cannot be smaller than or equal to 0");
    }
    if (code.endLine < code.beginLine) {
        valid = false;
        printError("End line cannot be smaller than begin line");
    }
    if (code.beginChar < 0) {
        valid = false;
        printError("Begin char cannot be smaller than 0");
    }
    if (code.endChar < 0) {
        valid = false;
        printError("End char cannot be smaller than 0");
    }
    if (code.beginLine == code.endLine && code.endChar < code.beginChar) {
        valid = false;
        printError("End char cannot be smaller than begin char when only one line is being changed");
    }
    if (code.lines.size() == 0) {
        valid = false;
        printError("Replacing code cannot be empty. To add an empty line add an empty string");
    }
    return valid;
}

Vulnerability getEditVuln(HWND hwnd, std::vector<Code> codes) {
    std::string name = getEditString(hwnd, IDC_VULNNAME);
    if (codes.size() == 0) {
        printError("Cannot create a vulnerability without code objects");
        return Vulnerability();
    }
    Vulnerability vuln(name, codes);
    return vuln;
}