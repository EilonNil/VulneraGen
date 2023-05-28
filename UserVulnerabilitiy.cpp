#include "UserVulnerability.h"

std::string getEditString(HWND hwnd, int item) {
    HWND edit = GetDlgItem(hwnd, item); 
    //get edit box HWND.
    char buf[1024];
    GetWindowText(edit, buf, 1024);
    SetWindowText(edit, ""); 
    //clear the window text.
    std::string line = buf;
    return line;
}

int getEditInt(HWND hwnd, int item) {
    std::string line = getEditString(hwnd, item);
    return atoi(line.c_str());
    //function that converts string to int.
}

Code getEditCode(HWND hwnd, strList lines) {
    std::string basePath = "C:\\Users\\Eilon\\Documents\\YudBetFinalProject\\juice-shop-master\\";
    std::string filePath = getEditString(hwnd, IDC_PATH);
    std::string fullPath = basePath + filePath;
    int beginLine = getEditInt(hwnd, IDC_BEGINLINE);
    int beginChar = getEditInt(hwnd, IDC_BEGINCHAR);
    int endLine = getEditInt(hwnd, IDC_ENDLINE);
    int endChar = getEditInt(hwnd, IDC_ENDCHAR);
    Code code(fullPath, beginLine, beginChar, endLine, endChar, lines);
    if (isCodeValid(code)) {
        return code;
    }
    return Code(); //empty code object because entered parameters are invalid
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
    if ((code.endLine - code.beginLine + 1) != code.lines.size()) {
        valid = false;
        printError("Number of lines added and number of lines removed need to be matched");
    }
    return valid;
}

Vulnerability getEditVuln(HWND hwnd, codeList codes) {
    std::string name = getEditString(hwnd, IDC_VULNNAME);
    if (codes.size() != 0) {
        //makes sure the vulnerability actually has code to change
        Vulnerability vuln(name, codes);
        return vuln;
    }
    
    printError("Cannot create a vulnerability without code objects");
    return Vulnerability(); //returns empty Vulnerability object in case of error
}