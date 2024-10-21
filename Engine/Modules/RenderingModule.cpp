#include "RenderingModule.hpp"
#include "../SimulationManager.hpp"
#include <iostream>

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
	museum.render(renderer);
	artistsManager.render(renderer);
}

void RenderingModule::present() {
	SDL_RenderPresent(renderer);
}
