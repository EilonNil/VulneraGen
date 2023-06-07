#pragma once
#include <Windows.h>
#include <iostream>

static DWORD notepadprocID;

void connectDLL(std::string dllPath);
void printNotepadMsg(std::string dllPath, std::string message);
std::string getDLLPath();
