//
// Created by larsv on 08/10/2024.
//

#include "CsvArtistStrategy.hpp"

bool CsvArtistStrategy::checkCompatibility(const std::vector<std::string>& data) {
	//Check if first line, and thus the format of the file matches "x,y,vx,vy"
	return (data[0].find("x,y,vx,vy") != std::string::npos);
}

void CsvArtistStrategy::parseStrategy(const std::vector<std::string>& data) {
	std::cout << "Csv" << std::endl;
}
