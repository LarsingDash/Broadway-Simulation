﻿//
// Created by larsv on 03/10/2024.
//

#include "Red.hpp"
#include "Blue.hpp"

void Red::handleInteraction(Tile& tile, Artist* artist) {
	tile.setState<Blue>();
}
