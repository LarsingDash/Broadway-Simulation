#define STB_IMAGE_IMPLEMENTATION

#include "RenderingModule.hpp"
#include <iostream>

RenderingModule::RenderingModule(SDL_Window* window, Museum* museum) : museum(museum) {
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		std::cerr << "Couldn't create renderer: " << SDL_GetError() << std::endl;
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
    clear();

    if (museum) {
        museum->render(renderer);
    }
}

void RenderingModule::present() {
	SDL_RenderPresent(renderer);
}
