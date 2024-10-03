//
// Created by larsv on 03/10/2024.
//

#ifndef BROADWAY_SIMULATION_FILEREADERTEMPLATE_HPP
#define BROADWAY_SIMULATION_FILEREADERTEMPLATE_HPP

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
	static void readFile(const std::string& path, SourceType sourceType, FileType fileType); 
};

#endif //BROADWAY_SIMULATION_FILEREADERTEMPLATE_HPP
