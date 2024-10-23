//
// Created by larsv on 11/10/2024.
//

#include "ArtistsManager.hpp"
#include "../Modules/RenderingModule.hpp"
#include <algorithm>

void ArtistsManager::update(Museum& museum, float delta) {
	//Update cycle
	for (const auto& artist: artists)
		if (artist) artist->update(museum, delta);

	//Check for deletionMarks
	auto it = std::remove_if(artists.begin(), artists.end(),
							 [](const std::unique_ptr<Artist>& cur) {
								 return cur->isMarkedForDeletion();
							 });

	//Erase artists marked for deletion
	if (it != artists.end()) artists.erase(it, artists.end());
}

void ArtistsManager::clearArtists() {
	artists.clear();
}

void ArtistsManager::addArtist(const glm::ivec2 tile, const glm::vec2 dir) {
	if (artists.size() >= 250) return;
	artists.emplace_back(std::make_unique<Artist>(glm::vec2{tile.x, tile.y} * RenderingModule::tileSize, dir, tile));
}

const std::vector<std::unique_ptr<Artist>>& ArtistsManager::getArtists() const { return artists; }
