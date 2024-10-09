//
// Created by larsv on 09/10/2024.
//

#include "TileState.hpp"
#include "../Museum.hpp"

TileState::TileState(const char& c) : letter{c}, config {Museum::colors[c]} {}

void TileState::render(SDL_Renderer* renderer, int x, int y, int tileSize) const {
	SDL_Rect tileRect = {x, y, tileSize, tileSize};
	SDL_SetRenderDrawColor(renderer, config.first.r, config.first.g,
						   config.first.b, config.first.a);
	SDL_RenderFillRect(renderer, &tileRect);
}
