#include "QuitCommand.hpp"
#include <iostream>

void QuitCommand::execute() {
    std::cout << "QuitCommand executed, setting shouldQuit to true." << std::endl;
    if(SimulationManager::getInstance().guiModule->isWindowOpen()) {
        SimulationManager::getInstance().guiModule->toggleFileSelectionWindow();
    }else{
        SimulationManager::getInstance().shouldQuit = true;
    }
}
