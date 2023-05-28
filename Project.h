#pragma once
#include "UserVulnerability.h"
typedef std::vector<Vulnerability> vulnList;
typedef std::vector<std::string> strList;
typedef std::vector<Code> codeList;

class Project
{
private:
	std::string projectPath;
	std::string vulnPath;
	vulnList newVulns;
	std::string userJsonPath;
public:
	Project(const std::string& ProjectPath, const std::string& vulnsPath, const vulnList& newVulns, const std::string& userJsonPath);
	vulnList readVulns();
	vulnList chooseVulns(const vulnList& vulns, std::vector<bool> vulnArr);
	bool createProject(const vulnList& vulns);
	bool runProject(std::vector<bool> vulnArr);
	bool changeBack(const vulnList& vulns);
	bool initalize(const vulnList& vulns);
	~Project();
};

