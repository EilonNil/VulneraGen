#include "Code.h"

Code::Code() {
	this->filePath = "null";
	this->beginLine = 0;
	this->beginChar = 0;
	this->endLine = 0;
	this->endChar = 0;
	this->lines = std::vector<std::string>();
}

Code::Code(const std::string filePath, const int beginLine, const int beginChar, const int endLine, const int endChar, const std::vector<std::string> lines) {
	this->filePath = filePath;
	this->beginLine = beginLine;
	this->beginChar = beginChar;
	this->endLine = endLine;
	this->endChar = endChar;
	this->lines = lines;
}

const Code& Code::operator=(const Code& other) {
	this->filePath = other.filePath;
	this->beginLine = other.beginLine;
	this->beginChar = other.beginChar;
	this->endLine = other.endLine;
	this->endChar = other.endChar;
	this->lines = other.lines;
	return *this;
}

Code::Code(const Code& other) {
	*this = other;
}

Code::~Code() {
	
}

bool Code::changeCode()
{
	/*std::fstream oFile;
	std::fstream iFile;

	iFile.open(this->filePath, std::ios::in);
	if (iFile.is_open()) {
		std::vector<std::string> lines;
		std::string line;
		while (std::getline(iFile, line)) {
			lines.push_back(line);
		}
		iFile.close();
		oFile.open(this->filePath, std::ios::out);
		for (int i = 0; i < lines.size(); i++) {
			if (i >= this->beginLine-1 && i <= this->endLine-1) {
				for (int j = 0; j < this->lines.size(); j++) {
					if (i != lines.size() - 1) {
						oFile << this->lines[j] << std::endl;
					}
					else {
						oFile << this->lines[j];
					}
				}
				i = this->endLine-1;
			}
			else {
				if (i != lines.size() - 1) {
					oFile << lines[i] << std::endl;
				}
				else {
					oFile << lines[i];
				}
			}
		}
		oFile.close();
	}
	else {
		return false;
	}*/
	std::ifstream file(this->filePath);
	std::vector<std::string> lines;
	std::string line;
	if (file.is_open()) {
		while (std::getline(file, line)) {
			lines.push_back(line);
		}
		file.close();
	}
	else {
		return false;
	}
	

	int thisLinesCount = 0;
	if (beginChar != 0 && endLine == beginLine) { //doesnt change the whole line but only changes one line
		if (endChar == 0) { // changes until the end of the line
			lines[beginLine - 1].replace(this->beginChar, lines[beginLine - 1].size() - beginChar, this->lines[0]);
		}
		else { // dont change the whole line
			lines[beginLine - 1].replace(this->beginChar, endChar - beginChar, this->lines[0]);
		}
	}
	else if (beginChar == 0 && endLine == beginLine) { //changes only the first line and fully
		if (endChar == 0) { // changes until the end of the line
			lines[beginLine - 1].replace(0, lines[beginLine - 1].size(), this->lines[0]);
		}
		else { // dont change the whole line
			lines[beginLine - 1].replace(0, endChar - beginChar, this->lines[0]);
		}
	}
	else if (beginChar != 0 && endChar != 0 && beginLine < endLine) { //changes multiple lines, first and last not fully
		lines[beginLine - 1].replace(this->beginChar, lines[beginLine - 1].size() - beginChar, this->lines[0]);
		lines[endLine - 1].replace(0, endChar, this->lines[this->lines.size() - 1]);
		thisLinesCount++;
		for (int i = beginLine; i < endLine - 1; i++) {
			lines[i].replace(0, lines[i].size(), this->lines[thisLinesCount]);
			thisLinesCount++;
		}
	}
	else if (beginChar != 0 && beginLine < endLine) { //doesnt change the whole first line and changes more than one line
		lines[beginLine - 1].replace(this->beginChar, lines[beginLine - 1].size() - beginChar, this->lines[0]);
		thisLinesCount++;
		for (int i = beginLine; i < endLine; i++) {
			lines[i].replace(0, lines[i].size(), this->lines[thisLinesCount]);
			thisLinesCount++;
		}
	}
	else if (beginLine < endLine && endChar != 0) { //changes the whole first line and changes more than one line and last line doesnt change all
		lines[endLine - 1].replace(0, endChar, this->lines[this->lines.size() - 1]);
		for (int i = beginLine - 1; i < endLine - 1; i++) {
			lines[i].replace(0, lines[i].size(), this->lines[thisLinesCount]);
			thisLinesCount++;
		}
	}
	else if (beginLine < endLine && endChar == 0) {//changes only full lines and more than 1
		for (int i = beginLine - 1; i < endLine; i++) {
			lines[i].replace(0, lines[i].size(), this->lines[thisLinesCount]);
			thisLinesCount++;
		}
	}


	std::ofstream output(this->filePath);
	if (output.is_open()) {
		for (const std::string& line : lines) {
			output << line << '\n';
		}
		output.close();
	}
	else {
		return false;
	}
	

	return true;
}
