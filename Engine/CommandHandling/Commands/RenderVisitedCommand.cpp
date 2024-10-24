//
// Created by larsv on 24/10/2024.
//

#include "RenderVisitedCommand.hpp"
#include "../../SimulationManager.hpp"

void RenderVisitedCommand::execute() {
	std::cout << "RenderVisitedCommand executed" << std::endl;
	SimulationManager::getInstance().pathfindingModule->toggleRenderVisited();
}