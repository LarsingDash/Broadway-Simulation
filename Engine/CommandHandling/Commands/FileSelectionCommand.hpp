//
// Created by 11896 on 11/10/2024.
//

#ifndef BROADWAY_SIMULATION_FILESELECTIONCOMMAND_HPP
#define BROADWAY_SIMULATION_FILESELECTIONCOMMAND_HPP
#include "../../FileReading/FileReaderTemplate.hpp"
#include <iostream>
#include "../Command.hpp"
class FileSelectionCommand :public Command{
    void execute() override{
        std::cout << "FileSelectionCommand executed" << std::endl;
		
		FileReaderTemplate::assignStrategies();
		
        FileReaderTemplate::readFileTemplate("..\\assets\\grid.txt", SourceType::File);
//		FileReaderTemplate::readFileTemplate("https://firebasestorage.googleapis.com/v0/b/dpa-files.appspot.com/o/grid.txt?alt=media", SourceType::Web);
		
//        FileReaderTemplate::readFileTemplate("..\\assets\\graph.xml", SourceType::File);
//		FileReaderTemplate::readFileTemplate("https://firebasestorage.googleapis.com/v0/b/dpa-files.appspot.com/o/graph.xml?alt=media", SourceType::Web);

        FileReaderTemplate::readFileTemplate("..\\assets\\artists.csv", SourceType::File);
    }
};


#endif //BROADWAY_SIMULATION_FILESELECTIONCOMMAND_HPP
