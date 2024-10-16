//
// Created by larsv on 03/10/2024.
//

#include "Blue.hpp"
#include "Yellow.hpp"

void Blue::handleInteraction(Tile* tile, bool mouseClick) {
	const auto& neighbors = tile->getNeighbors();
	int blueCount = 0;
	for (Tile* neighbor: neighbors) {
		if (blueCount >= 2) break;

		if (neighbor->currentState->letter != 'B') {	//TODO randomize
			neighbor->setState<Blue>();
			blueCount++;
		}
	}

	tile->setState<Yellow>();
}
