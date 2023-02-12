#include "Project.h"

Project::Project(std::string ProjectPath) {
	this->Projectpath = ProjectPath;
}

bool Project::runProject(bool vulnArr[]) {
	std::string command = "cd " + this->Projectpath + " & npm start";
	std::system(command.c_str());
	return true;
}

vulnList Project::readVulns(const std::string& VulnsPath) {
	vulnList vulns;
	vulns = convert(VulnsPath);
	return vulns;
}