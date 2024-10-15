//
// Created by larsv on 11/10/2024.
//

#ifndef BROADWAY_SIMULATION_ARTIST_HPP
#define BROADWAY_SIMULATION_ARTIST_HPP

#include <SDL_render.h>
#include <vec2.hpp>

class Artist {
	public:
		Artist(glm::vec2 pos, glm::vec2 dir);

		void render(SDL_Renderer* renderer) const;
		void update(float delta);
		void log() const;
	private:
		glm::vec2 pos;
		glm::vec2 dir;
		
		glm::vec2 offset{};
		glm::vec2 size{};
};


#endif //BROADWAY_SIMULATION_ARTIST_HPP
