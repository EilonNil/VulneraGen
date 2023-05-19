#pragma once
#include <Windows.h>
#include <Commctrl.h>
#include <tchar.h>
#include <iostream>
#include <atlbase.h>
#include "resource.h"
class Tooltip
{
private:
	HWND hwnd;
	int ID;
	std::string message;
public:
	Tooltip(const HWND& hwnd, const int& ID, const std::string& message);
	void create();
	~Tooltip();
};

void initiate(HWND hwnd);

