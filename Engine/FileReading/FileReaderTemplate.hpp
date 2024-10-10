//
// Created by larsv on 03/10/2024.
//

#ifndef BROADWAY_SIMULATION_FILEREADERTEMPLATE_HPP
#define BROADWAY_SIMULATION_FILEREADERTEMPLATE_HPP

#include "SourceStrategy/ISourceStrategy.hpp"
#include <iostream>

enum FileType {
	Map,
	Artist,
};

enum SourceType {
	File,
	Web,
};

class FileReaderTemplate {
	public:
		static void readFileTemplate(const std::string& pathOrURL, SourceType sourceType, FileType fileType);
};

#endif //BROADWAY_SIMULATION_FILEREADERTEMPLATE_HPP
