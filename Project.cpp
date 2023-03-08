#include "Project.h"

Project::Project(std::string ProjectPath, std::string vulnPath) {
	this->Projectpath = ProjectPath;
	this->vulnPath = vulnPath;
}

bool Project::runProject(std::vector<bool> vulnArr) {
	vulnList vulns = readVulns();
	bool success = createProject(chooseVulns(vulns, vulnArr));
	if (!success) {
		return false;
	}
	std::string command = "cd " + this->Projectpath + " & npm start";
	std::system(command.c_str());
//TODO: add the changing of files back to the original and delete .jsold files
	return true;
}

vulnList Project::readVulns() {
	vulnList vulns;
	vulns = convert(vulnPath);
	return vulns;
}

vulnList Project::chooseVulns(const vulnList& vulns, std::vector<bool> vulnArr)
{
	vulnList retVulns;
	for (int i = 0; i < vulnArr.size(); i++) {
		if (vulnArr[i]) {
			retVulns.push_back(vulns[i]);
		}
	}
	return retVulns;
}

bool Project::createProject(const vulnList& vulns)
{
	for (auto vuln : vulns) {
		bool success = vuln.changeCodes();
		if (!success) {
			return false;
		}
	}
	return true;
}
