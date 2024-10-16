//
// Created by larsv on 03/10/2024.
//

#ifndef BROADWAY_SIMULATION_RED_HPP
#define BROADWAY_SIMULATION_RED_HPP

#include "TileState.hpp"

class Tile;

class Red : public TileState {
	public:
		Red() : TileState('R') {}

		void handleInteraction(Tile* tile, bool mouseClick) override;
};

#endif //BROADWAY_SIMULATION_RED_HPP
