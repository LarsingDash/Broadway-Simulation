//
// Created by larsv on 03/10/2024.
//

#include "Red.hpp"
#include "Blue.hpp"

void Red::handleInteraction(Tile& tile, Artist* artist) {
	//Mark artist for deletion, if it wasn't a click action
	if (artist) artist->markForDeletion();

	tile.setState<Blue>();
}
