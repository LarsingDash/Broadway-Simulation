//
// Created by larsv on 08/10/2024.
//

#include "MuseumBuilder.hpp"

MuseumBuilder::MuseumBuilder() : autoNeighbors(false) {}

void MuseumBuilder::withAutoNeighbors() { autoNeighbors = true; }

void MuseumBuilder::addNeighbors(glm::vec2 tile, const std::vector<glm::vec2>& neighbors) {

}

void MuseumBuilder::finish() {

}
