#include "Project.h"

Project::Project(const std::string& ProjectPath, const std::string& vulnsPath, const vulnList& newVulns) {
	this->Projectpath = ProjectPath;
	this->vulnPath = vulnPath;
	this->newVulns = newVulns;
}

bool Project::runProject(std::vector<bool> vulnArr) {
	vulnList vulns = readVulns();
  	bool initSuccess = initalize(vulns);
	if (!initSuccess) {
		return false;
	}
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
	websiteClosed();
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
			printVuln(vulns[i]);
		}
	}
	for (auto item : this->newVulns) {
		retVulns.push_back(item);
		printVuln(item);
	}

	if (retVulns.size() != 0) {
		finishedScan();
	}
	else {
		noVulns();
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

bool Project::initalize(const vulnList& vulns) {
	vulnList uninitalizedList;
	bool unintialized = false;
	for (auto vuln : vulns) {
		for (auto code : vuln.getCodes()) {
			std::string oldPath = code.getFilePath() + "old";
			if (doesExist(oldPath)) {
				unintialized = true;
			}
		}
		if (unintialized) {
			uninitalizedList.push_back(vuln);
		}
		unintialized = false;
	}
	bool success = changeBack(uninitalizedList);
	return success;
}