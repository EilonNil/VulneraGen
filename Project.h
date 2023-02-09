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
public:
	Project(std::string ProjectPath);
	vulnList readVulns(const std::string& VulnsPath); //parses the json file with the vulns into dictionaries, 
	// then turns them into vulnerability objects in a vector according to the vuln type
	vulnList chooseVulns(const vulnList& vulns, bool vulnArr[3]); //algorithm that chooses vulnerabilities that do not collide
	Project createProject(const vulnList& Vulns); //creates the project itself and changes the files to have/not have chosen vulns
	bool runProject(bool vulnArr[]); //runs the project itself and returns if it ran succesfully or not
};


// submit button pressed -> 
// runProject(vulnArr from checkboxes) ->
// readVulns, createProject(chooseVulns(vulnArr)), system(npm install/start/both)
