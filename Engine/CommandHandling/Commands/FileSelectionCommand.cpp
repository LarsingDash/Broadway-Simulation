//
// Created by 11896 on 11/10/2024.
//

#include "FileSelectionCommand.hpp"
#include "../../SimulationManager.hpp"

void FileSelectionCommand::execute() {
    std::cout << "FileSelectionCommand executed" << std::endl;
//    FileReaderTemplate::assignStrategies();
//    FileReaderTemplate::readFileTemplate("..\\assets\\grid.txt", SourceType::File);
    SimulationManager::getInstance().guiModule->toggleFileSelectionWindow();
}