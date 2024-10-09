﻿//
// Created by larsv on 03/10/2024.
//

#ifndef BROADWAY_SIMULATION_YELLOW_HPP
#define BROADWAY_SIMULATION_YELLOW_HPP


#include "TileState.hpp"

class Yellow : public TileState {
	public:
		Yellow(): TileState('Y') {}
		void handleInteraction() override;
};


#endif //BROADWAY_SIMULATION_YELLOW_HPP
