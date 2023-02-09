#include <Windows.h>
#include "resource.h"
#include "Project.h"
#include <iostream>
bool xss = false;
bool sqlI = false;
bool vuln3 = false;
std::string path = "C:\\Users\\Eilon\\Documents\\YudBetFinalProject\\juice-shop-master";
//std::string path = "C:\\Users\\Eilon\\Downloads\\juice-shop-master\\juice-shop-master";


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
        case IDC_VULN3: {
            vuln3 = vuln3 ^ 1;
            break;
        }
        case IDC_BUTTON:
        {
            bool chosenVulns[3];
            chosenVulns[0] = xss;
            chosenVulns[1] = sqlI;
            chosenVulns[2] = vuln3;
            Project project(path);
            vulnList vlns = project.readVulns("C:\\Users\\Eilon\\Documents\\YudBetFinalProject\\Vulnerabilities.json");
            project.runProject(chosenVulns);
            PostQuitMessage(0);
            /*char trues[50] = "trues: ";
            char xss2[] = "xss ";
            char sqli2[] = "sqli ";
            char vuln32[] = "vuln3 ";
            if (xss) strcat_s(trues, xss2);
            if (sqlI) strcat_s(trues, sqli2);
            if (vuln3) strcat_s(trues, vuln32);
            MessageBox(hwnd, trues, "Warning", MB_OK);*/
            break;
        }
        case IDC_CANCEL:
        {
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
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_FORM), NULL, DlgProc);
}
