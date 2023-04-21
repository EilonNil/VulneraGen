#pragma once
#include "Json.h"
typedef std::vector<Vulnerability> vulnList;
typedef std::vector<std::string> strList;
typedef std::vector<Code> codeList;

class Project
{
private:
	std::string Projectpath;
	std::string vulnPath;
	vulnList newVulns;
public:
	Project(const std::string& ProjectPath, const std::string& vulnsPath, const vulnList& newVulns);
	vulnList readVulns();
	vulnList chooseVulns(const vulnList& vulns, std::vector<bool> vulnArr);
	bool createProject(const vulnList& vulns);
	bool runProject(std::vector<bool> vulnArr);
	bool changeBack(const vulnList& vulns);
	bool initalize(const vulnList& vulns);
};

