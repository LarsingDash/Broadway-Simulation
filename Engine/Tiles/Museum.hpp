#ifndef BROADWAY_SIMULATION_MUSEUM_HPP
#define BROADWAY_SIMULATION_MUSEUM_HPP

#include "SDL_render.h"
#include "Tile.hpp"
#include "TileStates/White.hpp"
#include "TileStates/Blue.hpp"
#include "TileStates/Grey.hpp"
#include "TileStates/Red.hpp"
#include "TileStates/Yellow.hpp"
#include <vector>
#include <unordered_map>
#include <random>

class Museum {
	public:
		Museum(int rows, int cols, int tileSize);

		void initializeRandomTiles();
		void render(SDL_Renderer* renderer);
		void setNeighbors();
		[[nodiscard]] int getRows() const;
		[[nodiscard]] int getCols() const;
		[[nodiscard]] glm::vec2 getTileSize() const;
		void setRows(int rows);
		void setCols(int cols);
		Tile& getTile(int row, int col);
		void setTiles(std::vector<std::vector<std::unique_ptr<Tile>>>&& tiles);

		static std::unordered_map<char, std::pair<SDL_Color, float>> colors;
	private:
		void _recalculateTileSize();
		
		std::vector<std::vector<std::unique_ptr<Tile>>> grid;
		int rows, cols;
		glm::vec2 tileSize;
};

#endif // BROADWAY_SIMULATION_MUSEUM_HPP
