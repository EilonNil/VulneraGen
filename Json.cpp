#include "Json.h"

vulnList convert(const std::string& vulnsPath) {
	std::string filepath = "C:\\Users\\Eilon\\Documents\\YudBetFinalProject\\Vulnerabilities.json";
	std::ifstream file(filepath);
	vulnList retList;

	json data = json::parse(file);

	for (auto element : data["Vulnerabilities"]) {
		json vuln = element;
		retList.push_back(vulnGenerator(vuln));
	}
	return retList;
}

codeList codesGenerator(json codes) {
	codeList ret;
	for (auto element : codes) {
		json code = element;
		ret.push_back(singleCodeGenerator(code));
	}
	return ret;
}

Code singleCodeGenerator(json code) {
	std::string basePath = "C:\\Users\\Eilon\\Documents\\YudBetFinalProject\\";
	std::string filePath = code["File Path"];
	std::string fullPath = basePath + filePath;
	int beginLine = code["Begin Line"];
	int beginChar = code["Begin Char"];
	int endLine = code["End Line"];
	int endChar = code["End Char"];
	std::vector<std::string> lines;
	for (auto element : code["Code"]) {
		lines.push_back(element["line"]);
	}
	Code ret(fullPath, beginLine, beginChar, endLine, endChar, lines);
	return ret;
}

Vulnerability vulnGenerator(json vuln) {
	std::string name = vuln["Name"];
	codeList list = codesGenerator(vuln["Codes"]);
	Vulnerability retVuln(name, list);
	return retVuln;
}
