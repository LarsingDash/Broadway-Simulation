//
// Created by larsv on 11/10/2024.
//

#include "ArtistsManager.hpp"
#include "../Tiles/Museum.hpp"

void ArtistsManager::render(SDL_Renderer* renderer) const {
	for (const auto& artist : artists) 
		artist->render(renderer);
}

void ArtistsManager::update(float delta) {
	for (const auto& artist : artists)
		artist->update(delta);
}

void ArtistsManager::clearArtists() {
	artists.clear();
}

void ArtistsManager::addArtist(const glm::vec2 tile, const glm::vec2 dir) {
	artists.emplace_back(std::make_unique<Artist>(tile * Museum::tileSize, dir));
}
