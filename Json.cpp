#include "Json.h"

/*
std::vector<strList> split(const strList& file) {
	std::vector<strList> ret;
	for (int i = 0; i < file.size(); i++) {
		strList lst;
		while (file[i] != "}" && file[i] != "{") {
			lst.push_back(file[i]);
			i++;
		}
		if (file[i] == "}") {
			ret.push_back(lst);
		}
	}
	return ret;
}

Pson parse(const strList& vuln) {
	Pson Pson;
	std::string readKey;
	std::string bracket = "\"";
	std::string line;
	int bracketPlaces[4];
	for (int i = 0; i < 4; i++) {
		bracketPlaces[i] = 4;
	}
	int bracketCount = 0;
	for (int i = 0; i < vuln.size(); i++) {
		line = vuln[i];
		for (int j = 0; j < line.size(); j++) {
			if (line[j] == bracket[0]) {
				bracketPlaces[bracketCount] = j;
				bracketCount++;
			}
		}//"name" [0] = 0; [1] = 5
		readKey = line.substr(bracketPlaces[0]+1, bracketPlaces[1] - bracketPlaces[0] - 1);
		if (readKey == "code") {

		}
		token a(line.substr(bracketPlaces[0] + 1, bracketPlaces[1] - bracketPlaces[0] - 1));
		token b(line);
		int aa = 5;
		token c = aa;
		bracketCount = 0;
	}
}
*/
vulnList convert(const std::string& vulnsPath) {
	std::string filepath = "C:\\Users\\Eilon\\Documents\\YudBetFinalProject\\Vulnerabilities.json";
	std::ifstream file(filepath);
	vulnList retList;

	json data = json::parse(file);

	for (auto& element : data["Vulnerabilities"]) {
		json vuln = element;
		retList.push_back(vulnGenerator(vuln));
	}
	return retList;
}

codeList codesGenerator(json codes) {
	codeList ret;
	for (auto& element : codes) {
		json code = element;
		ret.push_back(singleCodeGenerator(code));
	}
	return ret;
}

Code singleCodeGenerator(json code) {
	std::string filePath = code["File Path"];
	int beginLine = code["Begin Line"];
	int beginChar = code["Begin Char"];
	int endLine = code["End Line"];
	int endChar = code["End Char"];
	std::vector<std::string> lines;
	for (auto& element : code["Code"]) {
		lines.push_back(element["line"]);
	}
	Code ret(filePath, beginLine, beginChar, endLine, endChar, lines);
	return ret;
}

Vulnerability vulnGenerator(json vuln) {
	std::string name = vuln["Name"];
	codeList list = codesGenerator(vuln["Codes"]);
	Vulnerability retVuln(name, list);
	return retVuln;
}
