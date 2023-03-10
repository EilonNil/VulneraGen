#include "Project.h"

Project::Project(std::string ProjectPath, std::string vulnPath) {
	this->Projectpath = ProjectPath;
	this->vulnPath = vulnPath;
}

bool Project::runProject(std::vector<bool> vulnArr) {
	vulnList vulns = readVulns();
	vulnList chosenVulns = chooseVulns(vulns, vulnArr);
	bool success = createProject(chosenVulns);
	if (!success) {
		return false;
	}
	std::string command = "cd " + this->Projectpath + " & npm start";
	std::system(command.c_str());
	bool changeSucess = changeBack(chosenVulns);
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

bool Project::changeBack(const vulnList& vulns) {
	std::vector<strList> list;
	for (auto vuln : vulns) {
		list.push_back(vuln.getUniquePaths());
	}

	std::vector<strList> oldList = list;
	for (int i = 0; i < oldList.size(); i++) {
		for (int j = 0; j < oldList[i].size(); j++) {
			oldList[i][j] = oldList[i][j] + "old";
			bool success = moveCode(list[i][j], oldList[i][j]);
			if (!success) {
				return false;
			}
		}
		deleteFiles(oldList[i]);
	}
	return true;
}

void Project::deleteFiles(const strList& paths) {
	for (auto path : paths) {
		deleteFile(path);
	}
}

void Project::deleteFile(std::string path) {
	std::string command = "del " + path;
	std::system(command.c_str());
}
