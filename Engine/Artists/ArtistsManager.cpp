//
// Created by larsv on 11/10/2024.
//

#include "ArtistsManager.hpp"
#include "../Tiles/Museum.hpp"
#include <algorithm>

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

void ArtistsManager::removeArtist(Artist* artist) {
	//Find artist with matching memory address
	auto it = std::remove_if(artists.begin(), artists.end(),
							 [artist](const std::unique_ptr<Artist>& cur) {
								 return cur.get() == artist;
							 });
	
	//Remove found artist
	artists.erase(it, artists.end());	
}
