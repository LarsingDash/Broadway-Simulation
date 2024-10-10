//
// Created by larsv on 08/10/2024.
//

#include "TxtMapStrategy.hpp"

void TxtMapStrategy::parseMap(const std::vector<std::string>& data) {

	//0		-	rows=x,cols=y
	//1	
	//2		-	first letter definition
	//...	-	more letter definitions
	//Blank	-	end of letter definitions
	//...	-	rows of the grid

	try {
		//Rows - Cols
		std::string rowsString, colsString;
		_readGridSize(data[0], rowsString, colsString);

		int rows = std::stoi(rowsString);
		int cols = std::stoi(colsString);

		//Init builder
		auto builder = std::make_unique<MuseumBuilder>(rows, cols);
		builder->withAutoNeighbors();

		//Color format check
		if (!std::equal(data[1].cbegin(), data[1].cend(), "letter,rgb,weight")) {
			std::cerr << "Unexpected color formatting" << std::endl;
			return;
		}

		//Read colors till blank line is found
		int blankLineI = 2;
		while (!data[blankLineI].empty()) _readColor(*builder, data[blankLineI++]);

		int tileLineI = blankLineI + 1; //Increment in further to get to the start of the tiles

		//Continue reading file for tiles till the amount of rows specified or an empty line (end of file) is reached
		while (tileLineI <= rows + blankLineI && !data[tileLineI].empty()) {
			_readTile(*builder, data[tileLineI], tileLineI - blankLineI - 1, cols);
			tileLineI++;
		}

		//Finish builder
		builder->finish();
	} catch (const std::invalid_argument& e) {
		std::cerr << "Cols - Rows string to int:" << e.what() << std::endl;
		return;
	}
}

void TxtMapStrategy::_readGridSize(const std::string& line, std::string& rows, std::string& cols) {
	//When comma is found, switch to cols
	bool toCols = false;

	//Go through line and place all numbers in rows or cols
	for (const char& c: line) {
		if (isdigit(c)) {
			if (toCols) cols += c;
			else rows += c;
		} else if (c == ',') toCols = true;
	}
}

void TxtMapStrategy::_readColor(MuseumBuilder& builder, const std::string& line) {
	std::vector<std::string> segments(5);
	int segI = 0;

	//Store each segment, separated by comma's, into a segments vector
	for (const char& c: line) {
		//Go to next segment on comma
		if (c == ',') segI++;
		else {
			//Skip non-digits beyond first segment: skips rgb [] while keeping color letter
			if (segI != 0 && !isdigit(c)) continue;
			segments[segI] += c;
		}
	}

	try {
		builder.addColor(
				segments[0][0], //Letter (first character because color letter is always 1 character)
				{
						SDL_Color{
								static_cast<Uint8>(std::stoi(segments[1])),    //R
								static_cast<Uint8>(std::stoi(segments[2])),    //G
								static_cast<Uint8>(std::stoi(segments[3])),    //B
						},
						std::stoi(segments[4]) //Weight
				}
		);
	} catch (const std::invalid_argument& e) {
		std::cerr << "Invalid arguments on String to Int in _readColor()\n" << e.what() << std::endl;
	}
}

void TxtMapStrategy::_readTile(MuseumBuilder& builder, const std::string& line, int currentRowI, int cols) {
	//Choose the smallest between cols or length of the line to prevent crashing when they don't match
	int size = static_cast<int>(line.size());
	int amount = cols < size ? cols : size;

	//Read every character in the line (till 'amount') and make the corresponding tile
	for (int i = 0; i < amount; i++) {
		char letter = static_cast<char>(toupper(line[i]));

		switch (letter) {
			default: //'_' and unrecognised letters are set as White (blank)
				builder.addTile(glm::vec2(i, currentRowI), 'W');
				break;
			case 'R': //Everything else can be sorted out in addTile()
			case 'B':
			case 'Y':
			case 'G':
				builder.addTile(glm::vec2(i, currentRowI), letter);
				break;
		}
	}
}
