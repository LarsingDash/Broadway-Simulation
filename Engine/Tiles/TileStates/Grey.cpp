//
// Created by larsv on 03/10/2024.
//

#include "Grey.hpp"
#include "Red.hpp"

void Grey::handleInteraction(Tile& tile, Artist* artist) {
	interactionCount++;

	if (interactionCount >= 3) {
		tile.setState<Red>();
	}
}
