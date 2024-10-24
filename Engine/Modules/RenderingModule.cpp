#include "RenderingModule.hpp"
#include "../SimulationManager.hpp"
#include <iostream>

glm::vec2 RenderingModule::tileSize;

RenderingModule::RenderingModule(SDL_Window* window) :
		museum{*SimulationManager::getInstance().museum},
		artistsManager{*SimulationManager::getInstance().artistsManager} {
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		std::cerr << "Couldn't create renderer: " << SDL_GetError() << std::endl;
		return;
	}
}

RenderingModule::~RenderingModule() {
	SDL_DestroyRenderer(renderer);
}

void RenderingModule::clear() {
	SDL_SetRenderDrawColor(renderer, 25, 25, 25, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

void RenderingModule::draw() {
	if (WindowModule::recalculateTileSize) recalculateTileSize();

	//Museum
	for (int y = 0; y < museum.getRows(); ++y) {
		for (int x = 0; x < museum.getCols(); ++x) {
			TileState& state = *museum.getTile(x, y).currentState;

			SDL_FRect tileRect = {
					static_cast<float>(x) * tileSize.x, static_cast<float>(y) * tileSize.y,
					tileSize.x, tileSize.y
			};

			SDL_SetRenderDrawColor(renderer, state.config.first.r, state.config.first.g,
								   state.config.first.b, state.config.first.a);
			SDL_RenderFillRectF(renderer, &tileRect);
		}
	}

	//Artists
	if (!isRenderingActive) return;

	for (const auto& artist: artistsManager.getArtists()) {
		SDL_FRect tileRect = {artist->pos.x + Artist::offset.x,
							  artist->pos.y + Artist::offset.y,
							  Artist::size.x,
							  Artist::size.y};

		if (artist->isColliding) SDL_SetRenderDrawColor(renderer, 225, 0, 0, 255);
		else SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
		
		SDL_RenderFillRectF(renderer, &tileRect);
	}
}

void RenderingModule::present() {
	SDL_RenderPresent(renderer);
}

void RenderingModule::toggleRendering() { isRenderingActive = !isRenderingActive; }

void RenderingModule::recalculateTileSize() const {
	//Remove scaling
	for (const auto& artist: artistsManager.getArtists())
		artist->pos /= tileSize;

	//Recalculate scaling
	tileSize = glm::vec2{
			static_cast<float>(WindowModule::width) / static_cast<float>(museum.getCols()),
			static_cast<float>(WindowModule::height) / static_cast<float>(museum.getRows()),
	};
	WindowModule::recalculateTileSize = false;

	Artist::offset = tileSize / 6.f;
	Artist::size = tileSize / 3.f * 2.f;

	//Reapply scaling
	for (const auto& artist: artistsManager.getArtists())
		artist->pos *= tileSize;
}
