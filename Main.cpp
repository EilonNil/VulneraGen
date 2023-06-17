#include "Tooltip.h"
#include "Project.h"
#include "VulnerabilityExplanations.h"
bool xss = false;
bool sqlI = false;
bool unvalidated = false;
bool product = false;
bool admin = false;
std::string path = "C:\\Users\\Eilon\\Documents\\YudBetFinalProject\\juice-shop-master"; //base path
std::string vulnsPath = "C:\\Users\\Eilon\\Documents\\YudBetFinalProject\\Vulnerabilities.json";
std::string userVulnsPath = "C:\\Users\\Eilon\\Documents\\YudBetFinalProject\\UserVulnerabilities.json";
std::vector<std::string> linesOfCode;
std::vector<Code> codes;
std::vector<Vulnerability> newVulns;


LRESULT CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_INITDIALOG:
    {
        initiate(hwnd); //creates tooltips for relevant buttons
        printIntro(); //prints notepad intro to the system
    }
    break;
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
            printScan();

            std::vector<bool> chosenVulns;
            chosenVulns.push_back(xss);
            chosenVulns.push_back(sqlI);
            chosenVulns.push_back(unvalidated);
            chosenVulns.push_back(product);
            chosenVulns.push_back(admin);
            Project project(path, vulnsPath, newVulns, userVulnsPath);
            project.runProject(chosenVulns);
            //create the project object and run the project itself
            //after the user has inputted all the vulnerabilities
            //to insert. after the project is finished running
            //close the window.

            DestroyWindow(hwnd);
            break;
        }
        case IDC_CODEBTN:
        {
            std::string line = getEditString(hwnd, IDC_CODE);
            linesOfCode.push_back(line);
            //list that represents inputted lines of code
            //since last code object was created.
            break;
        }
        case IDC_NEWCODE:
        {
            Code code = getEditCode(hwnd, linesOfCode);
            if (code.getFilePath() != "null") {
                codes.push_back(code);
                //list that represents inputted code objects
                //since last vulnerability was created.
            }
            linesOfCode = strList();
            //empty the list.
            break;
        }
        case IDC_NEWVULN:
        {
            Vulnerability vuln = getEditVuln(hwnd, codes);
            if (vuln.getCodes().size() != 0) {
                newVulns.push_back(vuln);
                //list that represents all vulnerabilities
                //inputted by the user.
                codes = codeList(); 
                //empty the list.
            }
            break;
        }
        case IDC_XSSMORE:
        {
            MessageBoxA(NULL, xssExp.c_str(), "XSS explanation", MB_OK);
            break;
        }
        case IDC_SQLIMORE:
        {
            MessageBoxA(NULL, sqliExp.c_str(), "SQL Injection explanation", MB_OK);
            break;
        }
        case IDC_REDIRECTMORE:
        {
            MessageBoxA(NULL, redirExp.c_str(), "Unvalidated Redirects explanation", MB_OK);
            break;
        }
        case IDC_TAMPERMORE:
        {
            MessageBoxA(NULL, tamperExp.c_str(), "Product Tampering explanation", MB_OK);
            break;
        }
        case IDC_ADMINMORE:
        {
            MessageBoxA(NULL, adminExp.c_str(), "Admin Registration explanation", MB_OK);
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
    //inject the DLL into notepad.
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_FORM), NULL, DlgProc);
}
