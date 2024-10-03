//
// Created by larsv on 03/10/2024.
//

#include "FileSourceStrategy.hpp"
#include <iostream>
#include <filesystem>

std::unique_ptr<Source> FileSourceStrategy::fetchSource(const std::string& path) {
	//Open file stream
	std::ifstream file(path);
	if (!file.is_open()) {
		std::cerr << "Unable to open file" << std::endl;
		return nullptr;
	}
	
	//Remove possible BOM
	ISourceStrategy::removeBOM(file);

	//Create source
	std::unique_ptr<Source> source = std::make_unique<Source>();

	//Read file
	std::string line;
	while (std::getline(file, line))
		source->data.push_back(line);
	
	//Set extension
	source->extension = std::filesystem::path(path).extension().string().substr(1);
	
	//Transfer ownership
	return source;
}
