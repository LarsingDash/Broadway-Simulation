#ifndef BROADWAY_SIMULATION_MUSEUM_HPP
#define BROADWAY_SIMULATION_MUSEUM_HPP

#include "Tile.hpp"
#include "TileStates/White.hpp"
#include "TileStates/Blue.hpp"
#include "TileStates/Grey.hpp"
#include "TileStates/Red.hpp"
#include "TileStates/Yellow.hpp"
#include <SDL_render.h>
#include <vector>
#include <unordered_map>
#include <random>

class Museum {
	public:
		Museum();

		void render(SDL_Renderer* renderer);
		[[nodiscard]] int getRows() const;
		[[nodiscard]] int getCols() const;
		void setRows(int rows);
		void setCols(int cols);
		Tile& getTile(int row, int col);
		void setTiles(std::vector<std::vector<std::unique_ptr<Tile>>>&& tiles);

		static std::unordered_map<char, std::pair<SDL_Color, float>> colors;
		static glm::vec2 tileSize;
	private:
		void _recalculateTileSize() const;

		std::vector<std::vector<std::unique_ptr<Tile>>> grid;
		int rows, cols;
};

#endif // BROADWAY_SIMULATION_MUSEUM_HPP
