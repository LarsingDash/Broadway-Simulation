//
// Created by larsv on 09/10/2024.
//

#include "TileState.hpp"
#include "../Museum.hpp"

TileState::TileState(const char& c) : letter{c}, config{Museum::colors[c]}, interactionCount{0} {}

void TileState::render(SDL_Renderer* renderer, float x, float y, glm::vec2 tileSize) const {
	SDL_FRect tileRect = {x, y, tileSize.x, tileSize.y};
	SDL_SetRenderDrawColor(renderer, config.first.r, config.first.g,
						   config.first.b, config.first.a);
	SDL_RenderFillRectF(renderer, &tileRect);
}
