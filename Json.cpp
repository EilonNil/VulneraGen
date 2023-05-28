#include "Json.h"

vulnList convert(const std::string& vulnsPath) {
	std::ifstream file(vulnsPath);
	if (!file.is_open()) {
		printError("ERROR: cannot open file " + vulnsPath + " for reading");
		return vulnList();
		//in the case the file is missing or not enough permissions,
		//return empty list and display errors
	}
	vulnList retList;

	json data = json::parse(file);
	//the json object "data" will act like a
	//special list that represents the data 
	//inside the json.

	for (auto element : data["Vulnerabilities"]) {
		json vuln = element; 
		//vuln represents each vulnerability
		//in json form.
		retList.push_back(vulnGenerator(vuln));
	}
	return retList;
}

codeList codesGenerator(json codes) {
	codeList ret;
	for (auto element : codes) {
		json code = element;
		ret.push_back(singleCodeGenerator(code));
		//make a list of code objects and return it.
	}
	return ret;
}

Code singleCodeGenerator(json code) {
	std::string basePath = "C:\\Users\\Eilon\\Documents\\YudBetFinalProject\\juice-shop-master\\";
	std::string filePath = code["File Path"];
	std::string fullPath = basePath + filePath;
	//get the full file path.
	int beginLine = code["Begin Line"];
	int beginChar = code["Begin Char"];
	int endLine = code["End Line"];
	int endChar = code["End Char"];
	//all the integer attributes of the code object.
	std::vector<std::string> lines;
	for (auto element : code["Code"]) {
		lines.push_back(element["line"]);
	}
	//list of the lines of code.
	Code ret(fullPath, beginLine, beginChar, endLine, endChar, lines);
	//create the code object and return it.
	return ret;
}

Vulnerability vulnGenerator(json vuln) {
	std::string name = vuln["Name"];
	//vulnerability name.
	codeList list = codesGenerator(vuln["Codes"]);
	Vulnerability retVuln(name, list);
	//create the vulnerability and return it.
	return retVuln;
}
