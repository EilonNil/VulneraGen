#pragma once
#include <Windows.h>
#include <Commctrl.h>
#include <tchar.h>
#include <iostream>
#include <atlbase.h>
class Tooltip
{
private:
	HWND hwnd;
	int ID;
	std::string message;
public:
	Tooltip(const HWND hwnd, const int ID, const std::string message);
	void create();
	~Tooltip();
};

