//
// Created by larsv on 24/10/2024.
//

#include "RenderCollisionInfoCommand.hpp"
#include "../../SimulationManager.hpp"

void RenderCollisionInfoCommand::execute() {
	std::cout << "RenderCollisionInfoCommand executed" << std::endl;
	SimulationManager::getInstance().collisionModule->toggleCollisionInfo();
}
