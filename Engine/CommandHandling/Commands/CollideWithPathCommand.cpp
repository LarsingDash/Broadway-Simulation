//
// Created by larsv on 24/10/2024.
//

#include "CollideWithPathCommand.hpp"
#include "../../SimulationManager.hpp"

void CollideWithPathCommand::execute() {
	std::cout << "CollideWithPathCommand executed" << std::endl;
	SimulationManager::getInstance().collisionModule->toggleCollideWithPath();
}