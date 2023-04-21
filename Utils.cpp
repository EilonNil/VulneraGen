#include "Utils.h"

bool isIn(std::vector<std::string> list, std::string newPath)
{
	for (auto path : list) {
		if (path == newPath) {
			return true;
		}
	}
	return false;
}

bool moveCode(std::string to, std::string from)
{
	std::ifstream fromFile(from);
	std::ofstream toFile(to);
	std::string line;

	if (fromFile.is_open()) {
		while (std::getline(fromFile, line)) {
			toFile << line << '\n';
		}
		fromFile.close();
		toFile.close();
	}
	else {
		printError("ERROR: cannot open file " + from + " for reading");
		return false;
	}
	return true;
}

bool doesExist(std::string path) {
	std::ifstream check(path);
	return check.is_open();
}

void deleteFiles(const strList& paths) {
	for (auto path : paths) {
		deleteFile(path);
	}
}

void deleteFile(std::string path) {
	std::string command = "del " + path;
	std::system(command.c_str());
}

strList makeUnique(const strList& list) {
	strList uniq;
	for (auto path : list) {
		if (!isIn(uniq, path)) {
			uniq.push_back(path);
		}
	}

	return uniq;
}


strList makeOneDimensional(const std::vector<strList>& lists) {
	strList ret;
	for (auto list : lists) {
		for (auto item : list) {
			ret.push_back(item);
		}
	}

	return ret;
}

