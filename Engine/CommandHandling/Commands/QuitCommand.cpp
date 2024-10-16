#include "QuitCommand.hpp"
#include <iostream>

void QuitCommand::execute() {
    std::cout << "QuitCommand executed, setting shouldQuit to true." << std::endl;
    SimulationManager::getInstance().shouldQuit = true;
}
