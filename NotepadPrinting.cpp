#include "NotepadPrinting.h"

void printIntro() {
	std::string line1 = "Scanning for vulnerabilities...\n";
	printNotepadMsg(getDLLPath(), line1);
	std::string tripDot = "...\n";
	Sleep(500);
	for (int i = 0; i < 3; i++) {
		printNotepadMsg(getDLLPath(), tripDot);
		Sleep(500);
	}
}

void printVuln(Vulnerability vuln) {
	std::vector<strList> attributes = vuln.vulnToLst();
	std::string message = "found vulnerability " + vuln.getName();
	message += " in files:\n";
	for (auto item : attributes) {
		message += item[0];
		message += " line " + item[1];
		if (item[2] != "0") {
			message += " beggining at char " + item[2];
		}
		message += "\n";
	}
	printNotepadMsg(getDLLPath(), message);
	std::string fixing = "fixing...\n";
	std::string fixed = "fixed!\n";
	printNotepadMsg(getDLLPath(), fixing);
	Sleep(1000);
	printNotepadMsg(getDLLPath(), fixed);
}

void finishedScan() {
	std::string message = "finished scan. Starting website\n";
	printNotepadMsg(getDLLPath(), message);
	Sleep(123);
}

void noVulns() {
	std::string message = "no vulnerabilities found. Starting website\n";
	printNotepadMsg(getDLLPath(), message);
	Sleep(123);
}

void websiteClosed() {
	Sleep(500);
	std::string message = "\nwebsite has been closed. original code has been restored\n";
	printNotepadMsg(getDLLPath(), message);
	Sleep(123);
}