//
// Created by oknor on 10/3/2024.
//

#include "Tile.hpp"

void Tile::render(SDL_Renderer* renderer, int x, int y, int tileSize) const {
	SDL_Rect tileRect = {x, y, tileSize, tileSize};
	SDL_SetRenderDrawColor(renderer, currentState->color.r, currentState->color.g,
						   currentState->color.b, currentState->color.a);
	SDL_RenderFillRect(renderer, &tileRect);
}

void Tile::addNeighbor(Tile* neighbor) { neighbors.push_back(neighbor); }
