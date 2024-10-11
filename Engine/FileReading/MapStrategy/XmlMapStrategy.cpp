//
// Created by larsv on 08/10/2024.
//

#include "XmlMapStrategy.hpp"
#include <algorithm>

//Initialize map of actions
XmlMapStrategy::XmlMapStrategy() : tagActions{
		{"canvas",   [this](const std::string& line, bool isEnd) {
			//Create / Finish builder
			if (!isEnd) {
				//Read grid size
				int rows = -1, cols = -1;
				_readGridSize(line, rows, cols);

				//Open builder if size was parsed
				if (rows == -1 || cols == -1) return;
				builder = std::make_unique<MuseumBuilder>(rows, cols);
			} else builder->finish();

		}},
		{"nodeType", [this](const std::string& line, bool isEnd) {
			//Add color from format: nodeType tag="W" red="255" green="255" blue="255" weight="1"
			builder->addColor(
					XmlMapStrategy::_readChar(line, "tag"),
					{
							SDL_Color{
									static_cast<Uint8>(XmlMapStrategy::_readInt(line, "red")),
									static_cast<Uint8>(XmlMapStrategy::_readInt(line, "green")),
									static_cast<Uint8>(XmlMapStrategy::_readInt(line, "blue")),
							},
							XmlMapStrategy::_readInt(line, "weight")
					}
			);
		}},
		{"letter",   [this](const std::string& line, bool isEnd) {
			//Create / Unbind tile
			if (!isEnd) {
				//Bind currently working tile for neighbors
				currentTile = glm::ivec2{
						XmlMapStrategy::_readInt(line, "x"),
						XmlMapStrategy::_readInt(line, "y"),
				};

				//Create tile
				builder->addTile(currentTile, line[0]);
			}
		}},
		{"edge",     [this](const std::string& line, bool isEnd) {
			builder->addNeighbor(
					currentTile,
					glm::ivec2{
							XmlMapStrategy::_readInt(line, "x"),
							XmlMapStrategy::_readInt(line, "y"),
					}
			);
		}},
} {}

void XmlMapStrategy::parseMap(const std::vector<std::string>& data) {
	//Read all lines and decide action based on the tag and current state
	int lineI = 0;
	std::string cur;
	while (!(cur = data[lineI]).empty()) {
		//Read tag to get tagInfo
		_readTag(cur);
		lineI++;
	}
}

void XmlMapStrategy::_readTag(const std::string& line) {
	//Trim leading tabs
	std::string trimmed = line.substr(line.find_first_of('<') + 1);

	//Check if the tag starts with a /, indicating it's the end of something
	bool isEnd = false;
	if (trimmed[0] == '/') {
		//Mark end and trim out the /
		isEnd = true;
		trimmed = trimmed.substr(1, trimmed.size());
	}

	//Get first word by searching for the first alphabetical character
	auto it = std::find_if(trimmed.begin(), trimmed.end(), [](char c) { return !isalpha(c); });
	if (it == trimmed.end()) {
		std::cerr << "_readTag found no alphabetical character in tag" << std::endl;
		return;
	}
	const std::string tag = trimmed.substr(0, std::distance(trimmed.begin(), it));

	//Call the tag-specific action
	try {
		tagActions.at(tag)(trimmed, isEnd);
	} catch (const std::out_of_range& e) {
		//Check for color letter
		char first = trimmed[0];
		if (isalpha(first) && trimmed[1] == ' ' && builder->hasColor(first)) {
			tagActions.at("letter")(trimmed, isEnd);
		}

		//If also not a known letter: don't do anything with the error.
		//The tag can be ignored if it's in the actions map
	}
}

void XmlMapStrategy::_readGridSize(const std::string& line, int& rows, int& cols) {
	try {
		std::string rowsString, colsString;

		//When quotes open, start writing, switch to cols on close
		bool quotesOpen = false;
		bool toCols = false;

		//Go through line and place all numbers in rows or cols
		for (const char& c: line) {
			//Toggle quotes
			if (c == '\"') {
				quotesOpen = !quotesOpen;

				//Switch to cols when rows is done
				if (!quotesOpen) toCols = true;
			}
				//Other characters
			else if (quotesOpen && isdigit(c)) {
				if (toCols) colsString += c;
				else rowsString += c;
			}
		}

		rows = std::stoi(rowsString);
		cols = std::stoi(colsString);
	} catch (const std::invalid_argument& e) {
		std::cerr << "Cols - Rows string to int:" << e.what() << std::endl;
		return;
	}
}

char XmlMapStrategy::_readChar(const std::string& line, const std::string& target) {
	//Get the character at the first occurrence of target. Skip the target itself and the =" part
	return line.at(line.find(target) + target.size() + _readingOffset);
}

int XmlMapStrategy::_readInt(const std::string& line, const std::string& target) {
	try {
		//Find target
		int pos = static_cast<int>(line.find(target) + target.size() + _readingOffset);

		//Add all characters into result till closing quote is found
		std::string result;
		char cur;
		while ((cur = line[pos++]) != '\"') result += cur;

		//Return result as an int
		return std::stoi(result);
	} catch (const std::invalid_argument& e) {
		std::cout << "Invalid arguments at _readInt" << std::endl;
		return 0;
	}
}
