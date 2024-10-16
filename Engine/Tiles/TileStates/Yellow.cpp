//
// Created by larsv on 03/10/2024.
//

#include "Yellow.hpp"
#include "Grey.hpp"
#include "../../SimulationManager.hpp"
#include "../../SingletonRandom.hpp"

void Yellow::handleInteraction(Tile& tile, Artist* artist) {
	SimulationManager& manager = SimulationManager::getInstance();
	SingletonRandom& random = SingletonRandom::get_instance();
	
	glm::ivec2 pos = tile.getPos();
	auto getDirection = [&random]() {
		return random.RandomFloat(-7.5f, 7.5f);
	};
	
	float vx = getDirection();
	float vy = getDirection();
	
	manager.artistsManager->addArtist(
			{pos.x, pos.y},
			{vx, vy}
	);

	interactionCount++;

	if (interactionCount == 2) {
		tile.setState<Grey>();
	}
}
