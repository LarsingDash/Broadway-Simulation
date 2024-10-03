//
// Created by larsv on 03/10/2024.
//

#ifndef BROADWAY_SIMULATION_RED_HPP
#define BROADWAY_SIMULATION_RED_HPP

#include "../TileState.hpp"

class Red : public TileState {
	public:
		Red(): TileState(SDL_Color{255,0,0}, 1) {}
		void handleInteraction() override;
};


#endif //BROADWAY_SIMULATION_RED_HPP
