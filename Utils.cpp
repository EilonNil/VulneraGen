#include "Utils.h"

bool isIn(std::vector<std::string> list, std::string newPath)
{
	//is chosen string inside the list
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
		//moves all the code from file "from" to file "to".
		fromFile.close();
		toFile.close();
	}
	else {
		printError("ERROR: cannot open file " + from + " for reading");
		return false;
		//in case the from file could not be opened, display a relevant error and return false.
	}
	return true;
}

bool doesExist(std::string path) {
	//does the file exist
	std::ifstream check(path);
	return check.is_open();
}

void deleteFiles(const strList& paths) {
	for (auto path : paths) {
		deleteFile(path);
	}
	//calls the command on all the files in the list.
}

void deleteFile(std::string path) {
	std::string command = "del " + path;
	//cmd command to delete a file.
	std::system(command.c_str());
}

strList makeUnique(const strList& list) {
	strList uniq;
	for (auto path : list) {
		if (!isIn(uniq, path)) {
			uniq.push_back(path);
			//if the file path was not already added, then add it to the list.
			//if it already exists, do nothing.
		}
	}

	return uniq;
}

strList makeOneDimensional(const std::vector<strList>& lists) {
	strList ret;
	for (auto list : lists) {
		for (auto item : list) {
			ret.push_back(item);
			//pushes all the items of a 2 dimensional list
			//into a single list.
		}
	}

	return ret;
}

