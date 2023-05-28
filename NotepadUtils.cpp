#include "NotepadUtils.h"

void connectDLL(std::string dllPath) {
    STARTUPINFO startupInfo = { 0 };
    PROCESS_INFORMATION processInfo = { 0 };

    startupInfo.cb = sizeof(startupInfo);

    // Create the Notepad process.
    if (CreateProcessA("C:\\Windows\\System32\\Notepad.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, (LPSTARTUPINFOA)&startupInfo, &processInfo)) {
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
    }
    Sleep(1000);

    HWND nphwnd = FindWindowA("Notepad", NULL);
    //get the HWND of the notepad window.
    DWORD procid = GetProcessId(nphwnd);
    //get the process ID of the notepad application using it's HWND.
    GetWindowThreadProcessId(nphwnd, &procid);
    HANDLE newhwnd = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_VM_WRITE | PROCESS_ALL_ACCESS | PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, false, procid);
    //get access to the process.
    if (newhwnd == NULL) {
        std::cout << "Error: no window \'Notepad\' " << GetLastError() << std::endl;
        exit(0);
        //deal with error.
    }

    LPVOID allocated = VirtualAllocEx(newhwnd, NULL, 1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    //allocate enough memory to write the DLL path.
    if (allocated == NULL) {
        std::cout << "could not allocate address " << GetLastError() << std::endl;
        exit(0);
        //deal with error.
    }
    

    size_t written = 0;
    WriteProcessMemory(newhwnd, allocated, dllPath.data(), dllPath.size(), &written);
    //write inside the allocated memory the DLL path.
    CreateRemoteThread(newhwnd, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, allocated, 0, &procid);
    //make a thread that loads the DLL into notepad.
}


void printNotepadMsg(std::string dllPath, std::string message) {
	HINSTANCE hDLL = LoadLibrary(TEXT(dllPath.c_str()));
    //get access to the functions of the DLL

	typedef VOID(*PrintMessageFunc)(std::string);
	PrintMessageFunc lpfnPrintMessage = reinterpret_cast<PrintMessageFunc>(GetProcAddress(hDLL, "printMessage"));
    //get the function itself from the DLL

	lpfnPrintMessage(message);

	FreeLibrary(hDLL);
}

std::string getDLLPath() {
    std::string path = "C:\\Users\\Eilon\\source\\repos\\FinalProjectYudBet\\x64\\Debug\\Dll.dll";
    return path;
}