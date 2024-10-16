//
// Created by larsv on 03/10/2024.
//

#ifndef BROADWAY_SIMULATION_FILEREADERTEMPLATE_HPP
#define BROADWAY_SIMULATION_FILEREADERTEMPLATE_HPP

#include "SourceStrategy/ISourceStrategy.hpp"
#include "IParseStrategy.hpp"
#include <iostream>

enum SourceType {
	File,
	Web,
};

class FileReaderTemplate {
	public:
		static void readFileTemplate(const std::string& pathOrURL, SourceType sourceType);
		static std::vector<std::unique_ptr<IParseStrategy>> strategies;
		static void assignStrategies();
};

#endif //BROADWAY_SIMULATION_FILEREADERTEMPLATE_HPP
