#ifndef BROADWAY_SIMULATION_TILESTATE_HPP
#define BROADWAY_SIMULATION_TILESTATE_HPP

#include "SDL_pixels.h"
#include "SDL_render.h"
#include <iostream>
#include <vec2.hpp>

class TileState {
	public:
		explicit TileState(const char& c);;
		virtual ~TileState() = default;

		virtual void handleInteraction() = 0;

		void render(SDL_Renderer* renderer, float x, float y, glm::vec2 tileSize) const;

		const char letter;
		const std::pair<SDL_Color, float>& config;
};

#endif // BROADWAY_SIMULATION_TILESTATE_HPP
