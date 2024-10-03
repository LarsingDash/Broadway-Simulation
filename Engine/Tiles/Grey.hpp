//
// Created by larsv on 03/10/2024.
//

#ifndef BROADWAY_SIMULATION_GREY_HPP
#define BROADWAY_SIMULATION_GREY_HPP

#include "TileState.hpp"

class Grey : public TileState {
	public:
		Grey(): TileState(SDL_Color{150,150,150}, 1) {}
		void handleInteraction() override;
};


#endif //BROADWAY_SIMULATION_GREY_HPP
