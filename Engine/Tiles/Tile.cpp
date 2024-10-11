//
// Created by oknor on 10/3/2024.
//

#include "Tile.hpp"

void Tile::addNeighbor(Tile* neighbor) { neighbors.push_back(neighbor); }

void Tile::logTileData() const {
	//Divider
	std::cout << "----- " << currentState->letter << " -----" << std::endl;
	
	//Weight | Color
	std::cout << "Weight: " << currentState->config.second << " | Color: ("
			  << static_cast<int>(currentState->config.first.r) << ", "
			  << static_cast<int>(currentState->config.first.g) << ", "
			  << static_cast<int>(currentState->config.first.b) << ")" << std::endl;
	
	//Position | Neighbor
	std::cout << "At: (" << pos.x << ", " << pos.y << ")" << " | Neighbors: " << std::endl;
	for (const auto& neighbor : neighbors) {
		std::cout << "\t " << neighbor->currentState->letter << ": ("
		<< neighbor->pos.x << ", "
		<< neighbor->pos.y << ")" << std::endl;
	}
}
