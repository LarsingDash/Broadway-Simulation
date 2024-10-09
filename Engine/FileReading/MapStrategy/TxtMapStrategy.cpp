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

		builder->addTile({10, 10}, 'R');
		builder->addTile({11, 10}, 'B');
		builder->addTile({12, 10}, 'Y');
		builder->addTile({13, 10}, 'G');
		builder->addColor('R', {SDL_Color{255, 0, 0}, 1});

		//Finish builder
		builder->finish();
	} catch (const std::invalid_argument& e) {
		std::cerr << "Cols - Rows string to int:" << e.what() << std::endl;
		return;
	}
}

void TxtMapStrategy::_readGridSize(const std::string& line, std::string& rows, std::string& cols) {
	bool toCols = false;

	//Go through line and place all numbers in rows or cols
	for (const char& c: line) {
		if (isdigit(c)) {
			if (toCols) cols += c;
			else rows += c;
		} else if (c == ',') toCols = true;
	}
}