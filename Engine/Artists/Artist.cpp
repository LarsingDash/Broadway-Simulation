//
// Created by larsv on 11/10/2024.
//

#include "Artist.hpp"
#include "../Tiles/Museum.hpp"
#include "../Modules/WindowModule.hpp"

Artist::Artist(glm::vec2 pos, glm::vec2 dir) : pos{pos}, dir{dir} {
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
	//Update Position
	pos.x += (dir.x * Museum::tileSize.x) * delta;
	pos.y += (dir.y * Museum::tileSize.y) * delta;

	//Check bounds
	if (pos.x <= -offset.x) dir.x = abs(dir.x);    //Left
	if (pos.x >= static_cast<float>(WindowModule::width) - size.x - offset.x) dir.x = abs(dir.x) * -1;    //Right
	if (pos.y <= -offset.y) dir.y = abs(dir.y);    //Top
	if (pos.y >= static_cast<float>(WindowModule::height) - size.y - offset.y) dir.y = abs(dir.y) * -1;	//Bottom
}

[[maybe_unused]] void Artist::log() const {
	std::cout << "------" << std::endl;
	std::cout << "Pos: (" << pos.x << " | " << pos.y << ")" << std::endl;
	std::cout << "Dir: (" << dir.x << " | " << dir.y << ")" << std::endl;
}
