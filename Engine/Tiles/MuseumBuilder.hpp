//
// Created by larsv on 08/10/2024.
//

#ifndef BROADWAY_SIMULATION_MUSEUMBUILDER_HPP
#define BROADWAY_SIMULATION_MUSEUMBUILDER_HPP

#include "../Tiles/Museum.hpp"
#include "vec2.hpp"

class MuseumBuilder {
	public:
		MuseumBuilder();
		void withAutoNeighbors();

		template<class T>
		void addTile(const glm::vec2&& pos) {
			
		}

		void addNeighbors(glm::vec2 tile, const std::vector<glm::vec2>& neighbors);
		void finish();
	private:
		struct _builderTile {
			const glm::vec2 pos;
			const TileState& state;
		};

		std::vector<std::vector<_builderTile>> tiles;
		bool autoNeighbors;
};


#endif //BROADWAY_SIMULATION_MUSEUMBUILDER_HPP
