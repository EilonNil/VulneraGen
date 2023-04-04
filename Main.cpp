#include <Windows.h>
#include "resource.h"
#include "Project.h"
#include "UserVulnerability.h"
#include <iostream>
bool xss = false;
bool sqlI = false;
bool unvalidated = false;
bool product = false;
bool admin = false;
std::string path = "C:\\Users\\Eilon\\Documents\\YudBetFinalProject\\juice-shop-master";
//std::string path = "C:\\Users\\Eilon\\Downloads\\juice-shop-master\\juice-shop-master"; //secondary path
std::string vulnsPath = "C:\\Users\\Eilon\\Documents\\YudBetFinalProject\\Vulnerabilities.json";
//std::string dllPath = "C:\\Users\\Eilon\\source\\repos\\FinalProjectYudBet\\x64\\Debug\\Dll.dll";
std::vector<std::string> linesOfCode;
std::vector<Code> codes;
std::vector<Vulnerability> newVulns;


LRESULT CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_XSS: {
            xss = xss ^ 1;
            break;
        }
        case IDC_SQLI: {
            sqlI = sqlI ^ 1;
            break;
        }
        case IDC_UNVALIDATED: {
            unvalidated = unvalidated ^ 1;
            break;
        }
        case IDC_PRODUCT: {
            product = product ^ 1;
            break;
        }
        case IDC_ADMIN: {
            admin = admin ^ 1;
            break;
        }
        case IDC_BUTTON:
        {
            printIntro();

            std::vector<bool> chosenVulns;
            chosenVulns.push_back(xss);
            chosenVulns.push_back(sqlI);
            chosenVulns.push_back(unvalidated);
            chosenVulns.push_back(product);
            chosenVulns.push_back(admin);
            Project project(path, vulnsPath, newVulns);
            //vulnList vlns = project.readVulns();
            bool success = project.runProject(chosenVulns);
            //PostQuitMessage(0);


            DestroyWindow(hwnd);
            break;
        }
        case IDC_CODEBTN:
        {
            std::string line = getEditString(hwnd, IDC_CODE);
            linesOfCode.push_back(line);
            break;
        }
        case IDC_NEWCODE:
        {
            Code code = getEditCode(hwnd, linesOfCode);
            if (code.getFilePath() != "null") {
                codes.push_back(code);
            }
            break;
        }
        case IDC_NEWVULN:
        {
            Vulnerability vuln = getEditVuln(hwnd, codes);
            if (vuln.getCodes().size() != 0) {
                newVulns.push_back(vuln);
            }
            break;
        }
        case IDC_CANCEL:
        {
            //close notepad
            HWND notepadHandle = FindWindow(NULL, "Untitled - Notepad");
            if (notepadHandle == NULL) {
                notepadHandle = FindWindow(NULL, "*Untitled - Notepad");
            }
            PostMessage(notepadHandle, WM_CLOSE, 0, 0);
            
            DestroyWindow(hwnd);
            break;
        }
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_CLOSE:
        EndDialog(hwnd, 0);
    default:
        return FALSE;
    }

    return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow)
{
    connectDLL(getDLLPath());
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_FORM), NULL, DlgProc);
}
