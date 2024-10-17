//
// Created by larsv on 11/10/2024.
//

#include "ArtistsManager.hpp"
#include "../Tiles/Museum.hpp"
#include <algorithm>

void ArtistsManager::render(SDL_Renderer* renderer) const {
	if (!isRenderingActive) return;
	
	for (const auto& artist: artists)
		artist->render(renderer);
}

void ArtistsManager::update(float delta) {
	//Update cycle
	for (const auto& artist: artists)
		if (artist) artist->update(delta);

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
	artists.emplace_back(std::make_unique<Artist>(glm::vec2{tile.x, tile.y} * Museum::tileSize, dir, tile));
}

void ArtistsManager::toggleRendering() { isRenderingActive = !isRenderingActive; }
