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

void MuseumBuilder::addNeighbor(glm::ivec2 tile, const glm::ivec2& neighbor) {
	builderTiles[tile.y][tile.x]->neighbors.push_back(neighbor);
}

void MuseumBuilder::addNeighbors(glm::ivec2 tile, const std::vector<glm::ivec2>& neighbors) {
	builderTiles[tile.y][tile.x]->neighbors = neighbors;
}

void MuseumBuilder::addColor(const char c, const std::pair<SDL_Color, float>&& config) {
	colors[c] = config;
}

bool MuseumBuilder::hasColor(char c) {
	return colors.find(c) != colors.end();
}

void MuseumBuilder::finish() const {
	Museum& museum = *SimulationManager::getInstance().museum;

	//Initialize rows
	auto tiles = std::vector<std::vector<std::unique_ptr<Tile>>>(rows);
	for (int y = 0; y < rows; y++) {
		//Initialize columns
		tiles[y] = std::vector<std::unique_ptr<Tile>>(cols);

		for (int x = 0; x < cols; x++) {
			//When there is no tile, fill the blank space with white
			if (builderTiles[y][x] == nullptr) {
				(tiles[y][x] = std::make_unique<Tile>(x, y))->setState<White>();
				continue;
			}

			//Get letter
			const char letter = builderTiles[y][x]->letter;

			//Initialize tile	
			switch (letter) {
				default:
					(tiles[y][x] = std::make_unique<Tile>(x, y))->setState<White>();
					break;
				case 'R':
					(tiles[y][x] = std::make_unique<Tile>(x, y))->setState<Red>();
					break;
				case 'B':
					(tiles[y][x] = std::make_unique<Tile>(x, y))->setState<Blue>();
					break;
				case 'Y':
					(tiles[y][x] = std::make_unique<Tile>(x, y))->setState<Yellow>();
					break;
				case 'G':
					(tiles[y][x] = std::make_unique<Tile>(x, y))->setState<Grey>();
					break;
			}
		}
	}

	//Neighbors
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			if (autoNeighbors) {    //Auto
				if (y > 0) _checkAndAddNeighbor(*tiles[y][x], *tiles[y - 1][x]);
				if (y < rows - 1) _checkAndAddNeighbor(*tiles[y][x], *tiles[y + 1][x]);
				if (x > 0) _checkAndAddNeighbor(*tiles[y][x], *tiles[y][x - 1]);
				if (x < cols - 1) _checkAndAddNeighbor(*tiles[y][x], *tiles[y][x + 1]);
			} else if (builderTiles[y][x] != nullptr) {    //Manual
				for (const auto& neighbor: builderTiles[y][x]->neighbors) {
					_checkAndAddNeighbor(*tiles[y][x], *tiles[neighbor.y][neighbor.x]);
				}
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

void MuseumBuilder::_checkAndAddNeighbor(Tile& cur, Tile& neighbor) {
	if (neighbor.currentState->letter == 'W') return;
	cur.addNeighbor(&neighbor);
}
