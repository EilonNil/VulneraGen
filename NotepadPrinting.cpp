#include "NotepadPrinting.h"

void printIntro() {
	//message printed when notepad opens.
	std::string message = "This notepad application was opened remotely by this program.\nIt will display the phases of defending the website, errors, and other useful information.\n";
	printNotepadMsg(getDLLPath(), message);
}

void printScan() {
	std::string line1 = "Scanning for vulnerabilities...\n";
	printNotepadMsg(getDLLPath(), line1);
	std::string tripDot = "...\n";
	Sleep(500);
	for (int i = 0; i < 3; i++) {
		printNotepadMsg(getDLLPath(), tripDot);
		Sleep(500);
	}
}

void printVuln(std::string vuln) {
	//printing vulnerabilities that will be protected.
	std::string message = vuln;
	printNotepadMsg(getDLLPath(), message);
	std::string fixing = "Fixing...\n";
	std::string fixed = "Fixed!\n";
	printNotepadMsg(getDLLPath(), fixing);
	Sleep(1000);
	printNotepadMsg(getDLLPath(), fixed);
}

void finishedScan() {
	//in the case that there were chosen vulnerabilities.
	std::string message = "Finished scan. Starting website\n";
	printNotepadMsg(getDLLPath(), message);
	Sleep(123);
}

void noVulns() {
	//in the case that there were no chosen vulnerabilities.
	std::string message = "No vulnerabilities found. Starting website\n";
	printNotepadMsg(getDLLPath(), message);
	Sleep(123);
}

void websiteClosed() {
	//run at the end before finishing.
	Sleep(500);
	std::string message = "\nWebsite has been closed. original code has been restored.\n";
	printNotepadMsg(getDLLPath(), message);
	Sleep(123);
}

void printError(std::string error) {
	//print an error message.
	std::string message = error + "\n";
	printNotepadMsg(getDLLPath(), message);
}