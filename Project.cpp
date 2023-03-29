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
	if (!changeSucess) {
		return false;
	}
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
	std::vector<strList> list2D;
	for (auto vuln : vulns) {
		list2D.push_back(vuln.getUniquePaths());
	}
	strList list = makeUnique(makeOneDimensional(list2D));

	strList oldList = list;
	for (int i = 0; i < oldList.size(); i++) {
		oldList[i] = oldList[i] + "old";
		bool success = moveCode(list[i], oldList[i]);
		if (!success) {
			return false;
		}
	}
	deleteFiles(oldList);

	return true;
}

