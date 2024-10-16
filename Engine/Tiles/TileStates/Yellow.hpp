//
// Created by larsv on 03/10/2024.
//

#ifndef BROADWAY_SIMULATION_YELLOW_HPP
#define BROADWAY_SIMULATION_YELLOW_HPP


#include "TileState.hpp"
class Tile;
class Yellow : public TileState {
	public:
		Yellow(): TileState('Y') {}
    void handleInteraction(Tile* tile, bool mouseClick) override;
};


#endif //BROADWAY_SIMULATION_YELLOW_HPP
