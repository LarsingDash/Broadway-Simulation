//
// Created by larsv on 03/10/2024.
//

#ifndef BROADWAY_SIMULATION_BLUE_HPP
#define BROADWAY_SIMULATION_BLUE_HPP

#include "../TileState.hpp"

class Blue : public TileState {
	public:
		Blue(): TileState(SDL_Color{0,0,255}, 1) {}
		void handleInteraction() override;
};


#endif //BROADWAY_SIMULATION_BLUE_HPP
