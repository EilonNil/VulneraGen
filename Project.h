#pragma once
#include "Json.h"
#include "Vulnerability.h"
typedef std::vector<Vulnerability> vulnList;
typedef std::vector<std::string> strList;
typedef std::vector<Code> codeList;
class Project
{
private:
	std::string Projectpath;
	std::string vulnPath;
public:
	Project(std::string ProjectPath, std::string vulnsPath);
	vulnList readVulns(); //parses the json file with the vulns into dictionaries, 
	// then turns them into vulnerability objects in a vector according to the vuln type
	vulnList chooseVulns(const vulnList& vulns, std::vector<bool> vulnArr); //algorithm that chooses vulnerabilities that do not collide
	bool createProject(const vulnList& vulns); //creates the project itself and changes the files to have/not have chosen vulns
	bool runProject(std::vector<bool> vulnArr); //runs the project itself and returns if it ran succesfully or not
	bool changeBack(const vulnList& vulns);
};




// submit button pressed -> 
// runProject(vulnArr from checkboxes) ->
// vulns = readVulns(), createProject(chooseVulns(vulns, vulnArr)), system(npm install/start/both)
