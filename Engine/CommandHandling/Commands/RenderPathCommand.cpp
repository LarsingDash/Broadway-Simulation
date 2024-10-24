//
// Created by larsv on 24/10/2024.
//

#include "RenderPathCommand.hpp"
#include "../../SimulationManager.hpp"

void RenderPathCommand::execute() {
	std::cout << "RenderPathCommand executed" << std::endl;
	SimulationManager::getInstance().pathfindingModule->toggleRenderPath();
}