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

		void setRows(int r);
		void setCols(int c);

		template<class TileState>
		void addTile(const glm::ivec2& pos) {
			tiles[pos.x][pos.y] = _builderTile{std::make_unique<TileState>(), {}};
		}

		void addNeighbors(glm::ivec2 tile, const std::vector<glm::ivec2>& neighbors);
		void finish() const;
	private:
		struct _builderTile {
			std::unique_ptr<TileState> state;
			std::vector<glm::ivec2> neighbors;
		};

		std::vector<std::vector<_builderTile>> tiles;
		bool autoNeighbors;
		int rows = 0, cols = 0;
};

#endif //BROADWAY_SIMULATION_MUSEUMBUILDER_HPP
