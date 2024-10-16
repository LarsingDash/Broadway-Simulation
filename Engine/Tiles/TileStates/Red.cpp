//
// Created by larsv on 03/10/2024.
//

#include "Red.hpp"
#include "Blue.hpp"
#include "../../SimulationManager.hpp"

void Red::handleInteraction(Tile& tile, Artist* artist) {
	if (artist)
		SimulationManager::getInstance().artistsManager->removeArtist(artist);

	tile.setState<Blue>();
}
