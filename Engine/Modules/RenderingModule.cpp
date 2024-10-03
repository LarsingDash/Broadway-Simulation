#define STB_IMAGE_IMPLEMENTATION

#include "RenderingModule.hpp"
#include "../Tiles/Red.hpp"
#include "../Tiles/Blue.hpp"
#include "../Tiles/Yellow.hpp"
#include "../Tiles/Grey.hpp"
#include "../Tiles/White.hpp"
#include <iostream>
#include <vector>
#include <memory>

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
	SDL_SetRenderDrawColor(renderer, 25, 25, 25, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

void RenderingModule::draw() {
	const int gridSize = 30;
	const int squareSize = 20;

	std::vector<std::unique_ptr<TileState>> colors;
	
	colors.push_back(std::make_unique<Red>(Red()));
	colors.push_back(std::make_unique<Blue>(Blue()));
	colors.push_back(std::make_unique<Yellow>(Yellow()));
	colors.push_back(std::make_unique<Grey>(Grey()));
	colors.push_back(std::make_unique<White>(White()));

	for (int y = 0; y < gridSize; ++y) {
		for (int x = 0; x < gridSize; ++x) {
			SDL_Color color = colors[(x + y) % 5]->color;
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			SDL_Rect rect = {x * squareSize, y * squareSize, squareSize, squareSize};
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}

void RenderingModule::present() {
	SDL_RenderPresent(renderer);
}
