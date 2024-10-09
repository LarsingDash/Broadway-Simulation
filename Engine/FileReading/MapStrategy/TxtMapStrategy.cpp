//
// Created by larsv on 08/10/2024.
//

#include "TxtMapStrategy.hpp"

void TxtMapStrategy::parseMap(const std::vector<std::string>& data) {
	MuseumBuilder builder;

	//0		-	rows=x,cols=y
	//1	
	//2		-	first letter definition
	//...	-	more letter definitions
	//Blank	-	end of letter definitions
	//...	-	rows of the grid

	//Rows - Cols
	std::string rowsString, colsString;
	bool toCols = false;
	
	//Go through data[0] and place all numbers in rowsString or colsString
	for (const char& c: data[0]) {
		if (isdigit(c)) {
			if (toCols) colsString += c;
			else rowsString += c;
		} else if (c == ',') toCols = true;
	}
	
	//Strings to ints
	int rows;
	int cols;
	try {
		builder.setRows(std::stoi(rowsString));
		builder.setCols(std::stoi(colsString));
	} catch (const std::invalid_argument& e) {
		std::cerr << "Cols - Rows string to int:" << e.what() << std::endl;
		return;
	}

	std::cout << data[0] << std::endl;
	builder.finish();
}
