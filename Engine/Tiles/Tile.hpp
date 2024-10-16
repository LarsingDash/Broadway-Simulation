//
// Created by oknor on 10/3/2024.
//

#ifndef BROADWAY_SIMULATION_TILE_HPP
#define BROADWAY_SIMULATION_TILE_HPP

#include "TileStates/TileState.hpp"
#include <vector>
#include <memory>
#include <glm.hpp>

class TileState;

class Tile {
	public:
		std::unique_ptr<TileState> currentState;

		explicit Tile(const glm::ivec2&& pos) : currentState{nullptr}, pos{pos} {};

		Tile(int x, int y) : currentState{nullptr}, pos{x, y} {};

		template<class T>
		void setState() {
			currentState = std::make_unique<T>();
		}

		void logTileData() const;

		void addNeighbor(Tile* neighbor);

		[[nodiscard]] const std::vector<Tile*>& getNeighbors() const { return neighbors; }

	private:
		std::vector<Tile*> neighbors;
		glm::ivec2 pos;
};


#endif //BROADWAY_SIMULATION_TILE_HPP
