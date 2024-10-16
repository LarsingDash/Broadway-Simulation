//
// Created by larsv on 03/10/2024.
//

#ifndef BROADWAY_SIMULATION_BLUE_HPP
#define BROADWAY_SIMULATION_BLUE_HPP

#include "TileState.hpp"

class Tile;

class Blue : public TileState {
	public:
		Blue() : TileState('B') {}

		void handleInteraction(Tile* tile, bool mouseClick) override;
};

#endif //BROADWAY_SIMULATION_BLUE_HPP
