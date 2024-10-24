#ifndef BROADWAY_SIMULATION_MEMENTO_HPP
#define BROADWAY_SIMULATION_MEMENTO_HPP

#include <vector>
#include "fwd.hpp"
#include "SDL_pixels.h"
#include "detail/type_vec2.hpp"

class Memento {
	public:
		struct TileState {
			char letter;
			glm::ivec2 position;
			SDL_Color color;
			float weight;
			int interactionCount;
		};

		struct ArtistState {
			glm::vec2 position;
			glm::vec2 direction;
			glm::ivec2 lastTile;
			bool markedForDeletion;
		};

		std::vector<std::vector<TileState>> tileStates;
		std::vector<ArtistState> artistStates;

		Memento(const std::vector<std::vector<TileState>>& tiles,
				const std::vector<ArtistState>& artists)
				: tileStates(tiles), artistStates(artists) {}
};

#endif // BROADWAY_SIMULATION_MEMENTO_HPP
