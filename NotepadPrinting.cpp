#include "NotepadPrinting.h"

void printIntro() {
	//message printed when notepad opens.
	std::string message = "This notepad application was opened remotely by this program.\nIt will display information about the process, its status and errors.\n";
	printNotepadMsg(getDLLPath(), message);
}

void printScan() {
	std::string line1 = "Adjusting website...\n";
	printNotepadMsg(getDLLPath(), line1);
	std::string tripDot = "...\n";
	Sleep(500);
	for (int i = 0; i < 2; i++) {
		printNotepadMsg(getDLLPath(), tripDot);
		Sleep(500);
	}
}

void printVuln(std::string vuln) {
	//printing added vulnerabilities.
	std::string message = vuln;
	printNotepadMsg(getDLLPath(), message);
	std::string fixing = "Inserting...\n";
	std::string fixed = "Done!\n";
	printNotepadMsg(getDLLPath(), fixing);
	Sleep(1000);
	printNotepadMsg(getDLLPath(), fixed);
}

void finishedScan() {
	//in the case that there were chosen or created vulnerabilities.
	std::string message = "Process finished. Starting website\n";
	printNotepadMsg(getDLLPath(), message);
	Sleep(123);
}

void noVulns() {
	//in the case that there were no chosen or created vulnerabilities.
	std::string message = "No vulnerabilities added. Starting website\n";
	printNotepadMsg(getDLLPath(), message);
	Sleep(123);
}

void websiteClosed() {
	//run at the end before finishing.
	Sleep(500);
	std::string message = "\nWebsite has been closed. Original code has been restored.\n";
	printNotepadMsg(getDLLPath(), message);
	Sleep(123);
}

void printError(std::string error) {
	//print an error message.
	std::string message = error + "\n";
	printNotepadMsg(getDLLPath(), message);
}