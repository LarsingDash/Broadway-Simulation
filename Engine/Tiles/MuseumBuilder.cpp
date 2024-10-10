//
// Created by larsv on 08/10/2024.
//

#include "MuseumBuilder.hpp"

MuseumBuilder::MuseumBuilder(int r, int c) : rows{r}, cols{c}, autoNeighbors(false) {
	//Initialize rows
	builderTiles = std::vector<std::vector<std::unique_ptr<_builderTile>>>(rows);

	for (int y = 0; y < rows; y++) {
		//Initialize columns
		builderTiles[y] = std::vector<std::unique_ptr<_builderTile>>(cols);

		for (int x = 0; x < cols; x++) {
			builderTiles[y][x] = nullptr;
		}
	}
}

void MuseumBuilder::withAutoNeighbors() { autoNeighbors = true; }

void MuseumBuilder::addTile(const glm::ivec2& pos, char c) {
	builderTiles[pos.y][pos.x] = std::make_unique<_builderTile>(c);
}

void MuseumBuilder::addNeighbors(glm::ivec2 tile, const std::vector<glm::ivec2>& neighbors) {
	builderTiles[tile.y][tile.x]->neighbors = neighbors;
}

void MuseumBuilder::addColor(const char c, const std::pair<SDL_Color, float>&& config) {
	colors[c] = config;
}

void MuseumBuilder::finish() const {
	Museum& museum = *SimulationManager::museum;

	//Initialize rows
	auto tiles = std::vector<std::vector<std::unique_ptr<Tile>>>(rows);
	for (int y = 0; y < rows; y++) {
		//Initialize columns
		tiles[y] = std::vector<std::unique_ptr<Tile>>(cols);

		for (int x = 0; x < cols; x++) {
			//When there is no tile, fill the blank space with white
			if (builderTiles[y][x] == nullptr) {
				(tiles[y][x] = std::make_unique<Tile>())->setState<White>();
				continue;
			}

			//Get letter
			const char letter = builderTiles[y][x]->letter;

			//Initialize tile	
			switch (letter) {
				default:
					(tiles[y][x] = std::make_unique<Tile>())->setState<White>();
					break;
				case 'R':
					(tiles[y][x] = std::make_unique<Tile>())->setState<Red>();
					break;
				case 'B':
					(tiles[y][x] = std::make_unique<Tile>())->setState<Blue>();
					break;
				case 'Y':
					(tiles[y][x] = std::make_unique<Tile>())->setState<Yellow>();
					break;
				case 'G':
					(tiles[y][x] = std::make_unique<Tile>())->setState<Grey>();
					break;
			}
		}
	}

	//Reconfigure museum
	museum.setRows(rows);
	museum.setCols(cols);

	//Set colors
	for (auto& [c, value]: colors) {
		Museum::colors[c] = {value.first, value.second};
	}

	//Set new tiles
	museum.setTiles(std::move(tiles));
}
