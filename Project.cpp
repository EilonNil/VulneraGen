#include "Project.h"

Project::Project(const std::string& projectPath, const std::string& vulnsPath, const vulnList& newVulns, const std::string& userJsonPath) {
	this->projectPath = projectPath;
	this->vulnPath = vulnsPath;
	this->newVulns = newVulns;
	this->userJsonPath = userJsonPath;
}

bool Project::runProject(std::vector<bool> vulnArr) {
	//reads from the JSON the preset vulnerabilities.
	vulnList vulns = readVulns(); 
	//checks if last run crashed and deals with it
	//if the run did.
  	bool initSuccess = initalize(vulns);
	if (!initSuccess) {
		return false;
	}
	//returns the full list of vulnerabilites the system
	//wil insert.
	vulnList chosenVulns = chooseVulns(vulns, vulnArr);
	//inserts the chosen vulnerabilities.
	bool success = createProject(chosenVulns);
	if (!success) {
		return false;
	}
	//run the website
	std::string command = "cd " + this->projectPath + " & npm start";
	std::system(command.c_str());
	//change back to the original code.
	bool changeSucess = changeBack(chosenVulns);
	if (!changeSucess) {
		return false;
	}
	//display end message
	websiteClosed();
	return true;
}

vulnList Project::readVulns() {
	vulnList vulns;
	//call the function inside Json.cpp that will
	//parse the JSON file.
	vulns = convert(vulnPath);
	return vulns;
}

vulnList Project::chooseVulns(const vulnList& vulns, std::vector<bool> vulnArr)
{
	vulnList retVulns;
	//synchronize between the list of booleans from the user
	//and the list of vulnerabilities from the JSON.
	for (int i = 0; i < vulnArr.size(); i++) {
		if (vulnArr[i]) {
			retVulns.push_back(vulns[i]);
			Vulnerability vuln = vulns[i];
			printVuln(vuln.toString());
		}
	}
	//add the user generated vulnerabilities.
	for (auto item : this->newVulns) {
		retVulns.push_back(item);
		printVuln(item.toString());
	}
	//make the user vulns into a json in case of crash.
	VulnsIntoJson(this->newVulns, this->userJsonPath);

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
	//insert the chosen vulnerabilities.
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
	if (doesExist(this->userJsonPath)) {
		deleteFile(this->userJsonPath);
	}
	//deletes the json with the user vulnerability so the program will
	//know in the next run that all the code was restored successfully

	return true;
}

bool Project::initalize(const vulnList& vulns) {
	if (vulns.size() == 0) {
		return false;
	}
	vulnList uninitalizedList;
	bool unintialized = false;
	for (auto vuln : vulns) {
		for (auto code : vuln.getCodes()) {
			std::string oldPath = code.getFilePath() + "old";
			if (doesExist(oldPath)) {
				unintialized = true;
				//found an "old" file.
				//this means that this vulnerability was inserted
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
	bool userSuccess = true;
	if (doesExist(this->userJsonPath)) {
		userSuccess = changeBack(convert(this->userJsonPath));
	}
	bool success = changeBack(uninitalizedList);
	//calls the changeBack function with all the vulnerabilities that
	//not changed back in the last run of the project


	return success;
}

Project::~Project() {

}