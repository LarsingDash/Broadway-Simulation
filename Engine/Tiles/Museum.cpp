#include "Museum.hpp"
#include "../Modules/WindowModule.hpp"
#include "../SimulationManager.hpp"

std::unordered_map<char, std::pair<SDL_Color, float>> Museum::colors;

Museum::Museum() : rows(0), cols(0) {
	//Add default color for blank (white) tiles
	Museum::colors['W'] = {SDL_Color{255, 255, 255}, 1};
}

int Museum::getRows() const { return rows; }

int Museum::getCols() const { return cols; }

void Museum::setRows(int row) {
	rows = row;
	SimulationManager::getInstance().renderingModule->recalculateTileSize();
}

void Museum::setCols(int col) {
	cols = col;
	SimulationManager::getInstance().renderingModule->recalculateTileSize();
}

Tile& Museum::getTile(int row, int col) { return *grid[col][row]; }

void Museum::setTiles(std::vector<std::vector<std::unique_ptr<Tile>>>&& tiles) { grid = std::move(tiles); }
