//
// Created by 11896 on 11/10/2024.
//

#include "RenderArtistsCommand.hpp"
#include "../../SimulationManager.hpp"

void RenderArtistsCommand::execute() {
	std::cout << "RenderArtistsCommand executed" << std::endl;
	SimulationManager::getInstance().artistsManager->toggleRendering();
}