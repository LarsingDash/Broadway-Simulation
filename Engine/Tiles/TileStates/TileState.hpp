#ifndef BROADWAY_SIMULATION_TILESTATE_HPP
#define BROADWAY_SIMULATION_TILESTATE_HPP

#include "SDL_pixels.h"
#include "SDL_render.h"
#include "../Tile.hpp"
#include <iostream>
#include <vec2.hpp>

class Tile;

class TileState {
	public:
		explicit TileState(const char& c);
		virtual ~TileState() = default;

		virtual void handleInteraction(Tile* tile, bool mouseClick) = 0;

		void render(SDL_Renderer* renderer, float x, float y, glm::vec2 tileSize) const;

		const char letter;
		const std::pair<SDL_Color, float>& config;
	protected:
		int interactionCount;
};

#endif // BROADWAY_SIMULATION_TILESTATE_HPP
