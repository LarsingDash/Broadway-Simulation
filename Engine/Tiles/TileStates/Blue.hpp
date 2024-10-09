//
// Created by larsv on 03/10/2024.
//

#ifndef BROADWAY_SIMULATION_BLUE_HPP
#define BROADWAY_SIMULATION_BLUE_HPP

#include "TileState.hpp"

class Blue : public TileState {
	public:
		Blue(): TileState('B') {}
		void handleInteraction() override;
};


#endif //BROADWAY_SIMULATION_BLUE_HPP
