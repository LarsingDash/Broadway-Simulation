﻿//
// Created by larsv on 11/10/2024.
//

#include "Artist.hpp"
#include "../Tiles/Museum.hpp"
#include "../Modules/WindowModule.hpp"
#include "../SimulationManager.hpp"

Artist::Artist(glm::vec2 pos, glm::vec2 dir, glm::ivec2 startingTile) :
		pos{pos}, dir{dir},
		lastTile{startingTile}, markedForDeletion{false} {
	const glm::vec2& tileSize = Museum::tileSize;

	offset = tileSize / 6.f;
	size = tileSize / 3.f * 2.f;
}

void Artist::render(SDL_Renderer* renderer) const {

	SDL_FRect tileRect = {pos.x + offset.x,
						  pos.y + offset.y,
						  size.x,
						  size.y};

	SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
	SDL_RenderFillRectF(renderer, &tileRect);
}

void Artist::update(float delta) {
	const glm::vec2& tileSize = Museum::tileSize;

	//Update Position
	pos.x += (dir.x * Museum::tileSize.x) * delta;
	pos.y += (dir.y * Museum::tileSize.y) * delta;

	//Check bounds
	if (pos.x <= -offset.x) dir.x = abs(dir.x);    //Left
	if (pos.x >= static_cast<float>(WindowModule::width) - size.x - offset.x) dir.x = abs(dir.x) * -1;    //Right
	if (pos.y <= -offset.y) dir.y = abs(dir.y);    //Top
	if (pos.y >= static_cast<float>(WindowModule::height) - size.y - offset.y) dir.y = abs(dir.y) * -1;    //Bottom

	//Calculate the tile the artist is now on
	const glm::ivec2 tilePos{
			static_cast<int>((pos.x + offset.x + size.x / 2.f) / tileSize.x),
			static_cast<int>((pos.y + offset.y + size.y / 2.f) / tileSize.y)
	};

	//If artist has moved to a new tile, call that tile's interaction
	if (tilePos.x != lastTile.x || tilePos.y != lastTile.y) {
		lastTile = tilePos;
		Tile& tile = SimulationManager::getInstance().museum->getTile(tilePos.x, tilePos.y);
		tile.currentState->handleInteraction(tile, this);
	}
}

void Artist::markForDeletion() { markedForDeletion = true; }

bool Artist::isMarkedForDeletion() const {return markedForDeletion;}

[[maybe_unused]] void Artist::log() const {
	std::cout << "------" << std::endl;
	std::cout << "Pos: (" << pos.x << " | " << pos.y << ")" << std::endl;
	std::cout << "Dir: (" << dir.x << " | " << dir.y << ")" << std::endl;
}
