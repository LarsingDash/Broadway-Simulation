//
// Created by larsv on 03/10/2024.
//

#ifndef BROADWAY_SIMULATION_TILESTATE_HPP
#define BROADWAY_SIMULATION_TILESTATE_HPP

#include "SDL_pixels.h"

class TileState {
	public:
		TileState(SDL_Color color, float weight) : color{color}, weight{weight} {};
		virtual void handleInteraction() = 0;
		SDL_Color color;
		float weight;
};

#endif //BROADWAY_SIMULATION_TILESTATE_HPP
