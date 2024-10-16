//
// Created by larsv on 08/10/2024.
//

#include "CsvArtistStrategy.hpp"

bool CsvArtistStrategy::checkCompatibility(const std::vector<std::string>& data) {
	//Check if first line, and thus the format of the file matches "x,y,vx,vy"
	return (data[0].find("x,y,vx,vy") != std::string::npos);
}

void CsvArtistStrategy::parseStrategy(const std::vector<std::string>& data) {
	ArtistsManager& artistsManager = *SimulationManager::getInstance().artistsManager;

	artistsManager.clearArtists();

	int lineI = 1;
	while (lineI < data.size()) {
		//Read line and break it into the segments x, y, vx and vy
		std::vector<float> segments(4);
		_splitLine(data[lineI], segments);

		//Add new artist
		artistsManager.addArtist({segments[0], segments[1]}, {segments[2], segments[3]});

		//Inc
		lineI++;
	}
}

void CsvArtistStrategy::_splitLine(const std::string& line, std::vector<float>& segments) {
	int segI = 0;
	std::string segString;

	//Lambda vor converting
	const auto& convert = [&segments = segments, &segI, &segString]() {
		try {
			segments[segI] = std::stof(segString);
		} catch (const std::invalid_argument& e) {
			std::cerr << "Invalid input in _splitLine: " << e.what() << std::endl;
		}
	};

	//Keep scanning till a comma is found
	for (const char& c: line) {
		//Move to the next segment on a comma, unless the list is smaller than the amount of actual segments
		if (c == ',') {
			if (segI < segments.size()) {
				convert(); //Convert
				segString = ""; //Reset
				segI++; //Increment
			} else break;    //In case of incorrect size of segments
		} else segString += c; //Add any other character
	}

	//Add last segment
	convert();
}
