#pragma once
#include "Vulnerability.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
typedef std::vector<std::string> strList;
typedef std::vector<Vulnerability> vulnList;
typedef std::vector<Code> codeList;

/*union token {
	std::string string();
	int line();
	strList code();
};

class Pson
{

public:
	strList keys;
	std::vector<token> values;
};

std::vector<strList> split(const strList& file);
Pson parse(const strList& vuln);
Vulnerability convert(Pson);*/

codeList codesGenerator(json codes);
Code singleCodeGenerator(json code);
Vulnerability vulnGenerator(json vuln);
vulnList convert(const std::string& vulnsPath);

