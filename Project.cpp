#include "Project.h"

Project::Project(const std::string& projectPath, const std::string& vulnsPath, const vulnList& newVulns) {
	this->projectPath = projectPath;
	this->vulnPath = vulnsPath;
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
	std::string command = "cd " + this->projectPath + " & npm start";
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
			Vulnerability vuln = vulns[i];
			printVuln(vuln.toString());
		}
	}
	for (auto item : this->newVulns) {
		retVulns.push_back(item);
		printVuln(item.toString());
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
	//now we have a unique list with all the paths that were changed

	strList oldList = list;
	for (int i = 0; i < oldList.size(); i++) {
		oldList[i] = oldList[i] + "old";
		//make a list of all the changes files but with
		//the additional "old" file type so we can move 
		// the code from the "old" to the original.
		bool success = moveCode(list[i], oldList[i]);
		if (!success) {
			return false;
		}
	}
	deleteFiles(oldList);
	//delete all the "old" files so the project can run again smoothly.

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
				//found an "old" file.
				//this means that this vulnerability was protected
				//but was not changed back at the end of the process.
			}
		}
		if (unintialized) {
			uninitalizedList.push_back(vuln);
			//the vulnerability is only added after the getCodes() for loop
			//has ended because if one code inside the vulnerability was
			//found then there is a very very high chance all the others
			//were not changed back too so there would be multiple
			//insertions of the same vulnerability
		}
		unintialized = false;
	}
	bool success = changeBack(uninitalizedList);
	//calls the changeBack function with all the vulnerabilities that
	//not changed back in the last run of the project
	return success;
}

Project::~Project() {

}