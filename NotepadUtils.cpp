#include "NotepadUtils.h"

void connectDLL(std::string dllPath) {
    STARTUPINFO startupInfo = { 0 };
    PROCESS_INFORMATION processInfo = { 0 };

    // Set the size of the STARTUPINFO structure
    startupInfo.cb = sizeof(startupInfo);

    // Create the Notepad process
    if (CreateProcessA("C:\\Windows\\System32\\Notepad.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, (LPSTARTUPINFOA)&startupInfo, &processInfo)) {
        // Close the handles to the process and thread
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);


    }
    Sleep(1000);

    HWND nphwnd = FindWindowA("Notepad", NULL);
    DWORD procid = GetProcessId(nphwnd);
    GetWindowThreadProcessId(nphwnd, &procid);
    HANDLE newhwnd = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_VM_WRITE | PROCESS_ALL_ACCESS | PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, false, procid);
    if (newhwnd == NULL) {
        std::cout << "Error: no window \'Notepad\' " << GetLastError() << std::endl;
        exit(0);
    }

    LPVOID allocated = VirtualAllocEx(newhwnd, NULL, 1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (allocated == NULL) {
        std::cout << "could not allocate address " << GetLastError() << std::endl;
        exit(0);
    }

    size_t written = 0;
    WriteProcessMemory(newhwnd, allocated, dllPath.data(), dllPath.size(), &written);
    CreateRemoteThread(newhwnd, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, allocated, 0, &procid);
}


void printNotepadMsg(std::string dllPath, std::string message) {
	HINSTANCE hDLL = LoadLibrary(TEXT(dllPath.c_str()));

	// Check if the DLL was loaded successfully
	if (hDLL == NULL) {
		// Handle error
	}

	// Get a pointer to the "printMessage" function
	typedef VOID(*PrintMessageFunc)(std::string);
	PrintMessageFunc lpfnPrintMessage = reinterpret_cast<PrintMessageFunc>(GetProcAddress(hDLL, "printMessage"));

	// Check if the function was found
	if (lpfnPrintMessage == NULL) {
		// Handle error
	}
	// Call the function
	lpfnPrintMessage(message);

	// Free the DLL from memory
	FreeLibrary(hDLL);
}

std::string getDLLPath() {
    std::string path = "C:\\Users\\Eilon\\source\\repos\\FinalProjectYudBet\\x64\\Debug\\Dll.dll";
    return path;
}