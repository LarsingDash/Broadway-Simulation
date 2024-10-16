//
// Created by larsv on 11/10/2024.
//

#ifndef BROADWAY_SIMULATION_ARTISTSMANAGER_HPP
#define BROADWAY_SIMULATION_ARTISTSMANAGER_HPP

#include "Artist.hpp"
#include <vector>
#include <memory>

class ArtistsManager {
	public:
		void render(SDL_Renderer* renderer) const;
		void update(float delta);
		void clearArtists();
		void addArtist(glm::vec2 tile, glm::vec2 dir);
		void removeArtist(Artist* cur);
	private:
		std::vector<std::unique_ptr<Artist>> artists;
};


#endif //BROADWAY_SIMULATION_ARTISTSMANAGER_HPP
