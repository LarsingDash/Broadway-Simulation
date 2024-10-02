#define STB_IMAGE_IMPLEMENTATION

#include "RenderingModule.hpp"
#include <SDL.h>
#include <iostream>

RenderingModule::RenderingModule(SDL_Window* window) {
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		std::cerr << "Couldn't create renderer: " << SDL_GetError() << std::endl;
	}
}

RenderingModule::~RenderingModule() {
	SDL_DestroyRenderer(renderer);
}

void RenderingModule::clear() {
	SDL_SetRenderDrawColor(renderer,25, 25, 25, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

void RenderingModule::draw() {
	const int gridSize = 30;
	const int squareSize = 20;
	SDL_Color colors[] = {
			{255, 255, 0,   SDL_ALPHA_OPAQUE},
			{0,   0,   255, SDL_ALPHA_OPAQUE},
			{255, 0,   0,   SDL_ALPHA_OPAQUE},
			{128, 128, 128, SDL_ALPHA_OPAQUE},
			{255, 255, 255, SDL_ALPHA_OPAQUE}
	};

	for (int y = 0; y < gridSize; ++y) {
		for (int x = 0; x < gridSize; ++x) {
			SDL_Color color = colors[(x + y) % 5];
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			SDL_Rect rect = {x * squareSize, y * squareSize, squareSize, squareSize};
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}

void RenderingModule::present() {
	SDL_RenderPresent(renderer);
}
