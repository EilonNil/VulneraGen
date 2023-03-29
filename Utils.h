#pragma once
#include "Code.h"
typedef std::vector<std::string> strList;

bool isIn(std::vector<std::string> list, std::string newPath);
bool moveCode(std::string to, std::string from);
bool doesExist(std::string path);

void deleteFiles(const strList& paths);
void deleteFile(std::string path);
strList makeUnique(const strList& list);
strList makeOneDimensional(const std::vector<strList>& lists);
