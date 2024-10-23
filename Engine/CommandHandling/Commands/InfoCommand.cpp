//
// Created by larsv on 18/10/2024.
//

#include "InfoCommand.hpp"
#include "../../SimulationManager.hpp"

void InfoCommand::execute() {
	std::cout << "InfoCommand executed" << std::endl;
	SimulationManager::getInstance().guiModule->enableInfoWindow();
}
