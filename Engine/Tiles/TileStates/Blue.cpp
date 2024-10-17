//
// Created by larsv on 03/10/2024.
//

#include "Blue.hpp"
#include "Yellow.hpp"
#include "../../SingletonRandom.hpp"
#include <algorithm>

void Blue::handleInteraction(Tile& tile, Artist* artist) {
	const auto& neighbors = tile.getNeighbors();
	
	//Clone neighbor list
	std::vector<Tile*> copy(neighbors.size());
	std::copy(neighbors.begin(), neighbors.end(), copy.begin());

	//Shuffle and make the first blue
	std::shuffle(copy.begin(), copy.end(), SingletonRandom::get_instance().getEngine());
	copy[0]->setState<Blue>();
	
	//Remove the one that was just made blue
	copy.erase(copy.begin());
	
	//Shuffle and make the first blue
	std::shuffle(copy.begin(), copy.end(), SingletonRandom::get_instance().getEngine());
	copy[0]->setState<Blue>();

	//make itself yellow
	tile.setState<Yellow>();
}
