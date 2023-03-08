#pragma once
#include "Vulnerability.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
typedef std::vector<std::string> strList;
typedef std::vector<Vulnerability> vulnList;
typedef std::vector<Code> codeList;


codeList codesGenerator(json codes);
Code singleCodeGenerator(json code);
Vulnerability vulnGenerator(json vuln);
vulnList convert(const std::string& vulnsPath);

