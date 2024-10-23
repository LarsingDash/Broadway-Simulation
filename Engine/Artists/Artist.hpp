//
// Created by larsv on 11/10/2024.
//

#ifndef BROADWAY_SIMULATION_ARTIST_HPP
#define BROADWAY_SIMULATION_ARTIST_HPP

class Museum;

#include <SDL_render.h>
#include <vec2.hpp>

class Artist {
	public:
		Artist(glm::vec2 pos, glm::vec2 dir, glm::ivec2 startingTile);
		
		void update(Museum& museum, float delta);

		void markForDeletion();
		[[nodiscard]] bool isMarkedForDeletion() const;
		
		[[maybe_unused]] void log() const;
		
		static glm::vec2 offset;
		static glm::vec2 size;
		glm::vec2 pos;
	private:
		glm::vec2 dir;

		bool markedForDeletion;
		glm::ivec2 lastTile;
};


#endif //BROADWAY_SIMULATION_ARTIST_HPP
