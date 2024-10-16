//
// Created by larsv on 03/10/2024.
//

#include "Yellow.hpp"
#include "Grey.hpp"

void Yellow::handleInteraction(Tile* tile, bool mouseClick) {
	//TODO: Spawn an artist
	interactionCount++;
	if (interactionCount == 2) {
		tile->setState<Grey>();
	}
}
