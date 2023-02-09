#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
class Code
{
private:
	std::string filePath;
	int beginLine;
	int beginChar;
	int endLine;
	int endChar;
	std::vector<std::string> lines; //might change

public:
	Code();
	Code(const std::string filePath, const int beginLine, const int beginChar, const int endLine, const int endChar, const std::vector<std::string> lines);
	Code(const Code& other);
	const Code& operator=(const Code& other);
	~Code();
	bool changeCode();
};

