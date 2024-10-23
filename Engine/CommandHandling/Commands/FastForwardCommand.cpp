//
// Created by 11896 on 11/10/2024.
//

#include "FastForwardCommand.hpp"

void FastForwardCommand::execute() {
	std::cout << "FastForwardCommand executed" << std::endl;
    SimulationManager::getInstance().redo();

}