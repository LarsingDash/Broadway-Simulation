//
// Created by 11896 on 11/10/2024.
//

#include "PlayPauseCommand.hpp"
#include "../../SimulationManager.hpp"

void PlayPauseCommand::execute() {
	std::cout << "PlayPauseCommand executed" << std::endl;
	SimulationManager::getInstance().toggleRunning();
}