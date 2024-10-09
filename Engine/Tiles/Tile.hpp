//
// Created by oknor on 10/3/2024.
//

#ifndef BROADWAY_SIMULATION_TILE_HPP
#define BROADWAY_SIMULATION_TILE_HPP


#include <vector>
#include "TileStates/TileState.hpp"
#include "SDL_render.h"
#include <memory>

class Tile {
	public:
		std::unique_ptr<TileState> currentState;
		std::vector<Tile*> neighbors;

		Tile() : currentState{nullptr} {}

		template<class TileState>
		void setState() {
			currentState = std::make_unique<TileState>();
		}

		void render(SDL_Renderer* renderer, int x, int y, int tileSize) const;

		void addNeighbor(Tile* neighbor);
};


#endif //BROADWAY_SIMULATION_TILE_HPP
