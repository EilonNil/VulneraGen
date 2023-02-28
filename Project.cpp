#include "Project.h"

Project::Project(std::string ProjectPath, std::string vulnPath) {
	this->Projectpath = ProjectPath;
	this->vulnPath = vulnPath;
}

bool Project::runProject(std::vector<bool> vulnArr) {
	vulnList vulns = readVulns();
	std::string command = "cd " + this->Projectpath + " & npm start";
	std::system(command.c_str());
	return true;
}

vulnList Project::readVulns() {
	vulnList vulns;
	vulns = convert(vulnPath);
	return vulns;
}