﻿//
// Created by larsv on 03/10/2024.
//

#ifndef BROADWAY_SIMULATION_RED_HPP
#define BROADWAY_SIMULATION_RED_HPP

#include "TileState.hpp"

class Red : public TileState {
	public:
		Red(): TileState('R') {}
		void handleInteraction() override;
};


#endif //BROADWAY_SIMULATION_RED_HPP
