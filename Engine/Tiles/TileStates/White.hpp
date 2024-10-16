//
// Created by larsv on 03/10/2024.
//

#ifndef BROADWAY_SIMULATION_WHITE_HPP
#define BROADWAY_SIMULATION_WHITE_HPP

#include "TileState.hpp"

class Tile;

class White : public TileState {
	public:
		White() : TileState('W') {}

		void handleInteraction(Tile* tile, bool mouseClick) override;
};

#endif //BROADWAY_SIMULATION_WHITE_HPP
