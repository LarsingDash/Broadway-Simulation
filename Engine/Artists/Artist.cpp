//
// Created by larsv on 11/10/2024.
//

#include "Artist.hpp"
#include "../Modules/WindowModule.hpp"
#include "../SimulationManager.hpp"

glm::vec2 Artist::offset{};
glm::vec2 Artist::size{};

Artist::Artist(glm::vec2 pos, glm::vec2 dir) :
		pos{pos}, dir{dir} {}

void Artist::update(float delta) {
	const glm::vec2& tileSize = RenderingModule::tileSize;

	//Update Position
	pos.x += (dir.x * tileSize.x) * delta;
	pos.y += (dir.y * tileSize.y) * delta;

	//Check bounds
	if (pos.x <= -offset.x) dir.x = abs(dir.x);    //Left
	if (pos.x >= static_cast<float>(WindowModule::width) - size.x - offset.x) dir.x = abs(dir.x) * -1;    //Right
	if (pos.y <= -offset.y) dir.y = abs(dir.y);    //Top
	if (pos.y >= static_cast<float>(WindowModule::height) - size.y - offset.y) dir.y = abs(dir.y) * -1;    //Bottom
}

[[maybe_unused]] void Artist::log() const {
	std::cout << "------" << std::endl;
	std::cout << "Pos: (" << pos.x << " | " << pos.y << ")" << std::endl;
	std::cout << "Dir: (" << dir.x << " | " << dir.y << ")" << std::endl;
}
