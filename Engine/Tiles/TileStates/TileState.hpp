#ifndef BROADWAY_SIMULATION_TILESTATE_HPP
#define BROADWAY_SIMULATION_TILESTATE_HPP

#include <iostream>
#include <vec2.hpp>
#include "SDL_pixels.h"
#include "SDL_render.h"

class TileState {
	public:
		explicit TileState(const char& c);;
		virtual ~TileState() = default;

		virtual void handleInteraction() = 0;

		virtual void logTileData() {
			std::cout << letter << " clicked: Weight=" << config.second << ", Color (RGBA): "
					  << static_cast<int>(config.first.r) << ", "
					  << static_cast<int>(config.first.g) << ", "
					  << static_cast<int>(config.first.b) << ", "
					  << static_cast<int>(config.first.a) << ", Type: " << typeid(*this).name() << std::endl;
		}

		void render(SDL_Renderer* renderer, float x, float y, glm::vec2 tileSize) const;

		const char letter;
		const std::pair<SDL_Color, float>& config;
};

#endif // BROADWAY_SIMULATION_TILESTATE_HPP
