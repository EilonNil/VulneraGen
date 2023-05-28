#pragma once
#include <vector>
#include <fstream>
#include <string>
#include "NotepadPrinting.h"
typedef std::vector<std::string> strList;

class Code
{
private:
	std::string filePath;
	int beginLine;
	int beginChar;
	int endLine;
	int endChar;
	strList lines;

public:
	Code();
	Code(const std::string filePath, const int beginLine, const int beginChar, const int endLine, const int endChar, const std::vector<std::string> lines);
	const Code& operator=(const Code& other);
	Code(const Code& other);
	bool changeCode();
	std::string getFilePath();
	strList codeToLst();
	~Code();
	friend bool isCodeValid(Code code);
	friend std::string codeIntoJson(Code code);
};

