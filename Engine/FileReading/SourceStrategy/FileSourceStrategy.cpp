//
// Created by larsv on 03/10/2024.
//

#include "FileSourceStrategy.hpp"
#include <iostream>

bool FileSourceStrategy::fetchSource(const std::string& path, std::vector<std::string>& data) {
	//Open file stream
	std::ifstream file(path);
	if (!file.is_open()) {
		std::cerr << "Unable to open file" << std::endl;
		return false;
	}

	//Remove possible BOM
	removeBOM(file);

	//Read file
	std::string line;
	while (std::getline(file, line))
		data.push_back(line);

	return true;
}
