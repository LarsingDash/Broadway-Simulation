//
// Created by larsv on 11/10/2024.
//

#include "ArtistsManager.hpp"
#include "../Modules/RenderingModule.hpp"

void ArtistsManager::update(float delta) {
	//Update cycle
	for (const auto& artist: artists)
		if (artist) artist->update(delta);
}

void ArtistsManager::clearArtists() {
	artists.clear();
}

void ArtistsManager::addArtist(const glm::ivec2 tile, const glm::vec2 dir) {
	if (artists.size() >= 250) return;
	artists.emplace_back(std::make_unique<Artist>(glm::vec2{tile.x, tile.y} * RenderingModule::tileSize, dir));
}

const std::vector<std::unique_ptr<Artist>>& ArtistsManager::getArtists() const { return artists; }
