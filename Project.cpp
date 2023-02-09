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
	/*std::fstream iFile;
	iFile.open(VulnsPath, std::ios::in);
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(iFile, line)) {
		lines.push_back(line);
	}
	std::vector<strList> splitted = split(lines);
	for (int i = 0; i < splitted.size(); i++) {
		vulns.push_back(convert(parse(splitted[i])));
	}*/
	return vulns;
}