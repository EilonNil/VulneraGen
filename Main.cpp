#include <Windows.h>
#include "resource.h"
#include "Project.h"
#include <iostream>
bool xss = false;
bool sqlI = false;
bool unvalidated = false;
bool product = false;
bool admin = false;
std::string path = "C:\\Users\\Eilon\\Documents\\YudBetFinalProject\\juice-shop-master";
//std::string path = "C:\\Users\\Eilon\\Downloads\\juice-shop-master\\juice-shop-master"; //secondary path
std::string vulnsPath = "C:\\Users\\Eilon\\Documents\\YudBetFinalProject\\Vulnerabilities.json";


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
            std::vector<bool> chosenVulns;
            chosenVulns.push_back(xss);
            chosenVulns.push_back(sqlI);
            chosenVulns.push_back(unvalidated);
            chosenVulns.push_back(product);
            chosenVulns.push_back(admin);
            Project project(path, vulnsPath);
            //vulnList vlns = project.readVulns();
            bool success = project.runProject(chosenVulns);
            //PostQuitMessage(0);

            DestroyWindow(hwnd);
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
