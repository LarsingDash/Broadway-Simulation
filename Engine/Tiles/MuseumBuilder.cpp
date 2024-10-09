//
// Created by larsv on 08/10/2024.
//

#include "MuseumBuilder.hpp"

MuseumBuilder::MuseumBuilder() : autoNeighbors(false) {}

void MuseumBuilder::setCols(int c) { cols = c; }

void MuseumBuilder::setRows(int r) { rows = r; }

void MuseumBuilder::withAutoNeighbors() { autoNeighbors = true; }

void MuseumBuilder::addNeighbors(glm::ivec2 tile, const std::vector<glm::ivec2>& neighbors) {

}

void MuseumBuilder::finish() const {
	std::cout << "BUILDER: " << std::endl;
	std::cout << rows << std::endl;
	std::cout << cols << std::endl;
}

