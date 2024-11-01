﻿//
// Created by larsv on 08/10/2024.
//

#ifndef BROADWAY_SIMULATION_MUSEUMBUILDER_HPP
#define BROADWAY_SIMULATION_MUSEUMBUILDER_HPP

#include "../SimulationManager.hpp"
#include <vec2.hpp>

class MuseumBuilder {
	public:
		MuseumBuilder(int r, int c);
		void withAutoNeighbors();

		void addTile(const glm::ivec2& pos, char c);
		[[maybe_unused]] void addNeighbor(glm::ivec2 tile, const glm::ivec2& neighbor);
		[[maybe_unused]] void addNeighbors(glm::ivec2 tile, const std::vector<glm::ivec2>& neighbors);
		void addColor(char c, const std::pair<SDL_Color, float>&& config);
		bool hasColor(char c);

		void finish() const;
	private:
		struct _builderTile {
			char letter;
			std::vector<glm::ivec2> neighbors;

			explicit _builderTile(char c) : letter(c), neighbors{} {}
		};

		static void _checkAndAddNeighbor(Tile& cur, Tile& neighbor);

		std::vector<std::vector<std::unique_ptr<_builderTile>>> builderTiles;
		std::unordered_map<char, std::pair<SDL_Color, float>> colors;

		bool autoNeighbors;
		int rows = 0, cols = 0;
};

#endif //BROADWAY_SIMULATION_MUSEUMBUILDER_HPP
