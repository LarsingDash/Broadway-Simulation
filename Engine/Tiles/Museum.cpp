#include "Museum.hpp"
#include "../Modules/WindowModule.hpp"

std::unordered_map<char, std::pair<SDL_Color, float>> Museum::colors;
glm::vec2 Museum::tileSize;

Museum::Museum() : rows(0), cols(0) {
	//Add default color for blank (white) tiles
	Museum::colors['W'] = {SDL_Color{255, 255, 255}, 1};
}

void Museum::render(SDL_Renderer* renderer) {
	if (WindowModule::recalculateTileSize) _recalculateTileSize();

	for (int y = 0; y < rows; ++y) {
		for (int x = 0; x < cols; ++x) {
			grid[y][x]->currentState->render(
					renderer,
					static_cast<float>(x) * tileSize.x,
					static_cast<float>(y) * tileSize.y,
					tileSize
			);
		}
	}
}

int Museum::getRows() const { return rows; }

int Museum::getCols() const { return cols; }

void Museum::setRows(int row) {
	rows = row;
	_recalculateTileSize();
}

void Museum::setCols(int col) {
	cols = col;
	_recalculateTileSize();
}

Tile& Museum::getTile(int row, int col) { return *grid[col][row]; }

void Museum::setTiles(std::vector<std::vector<std::unique_ptr<Tile>>>&& tiles) { grid = std::move(tiles); }

void Museum::_recalculateTileSize() const {
	Museum::tileSize = glm::vec2{
			static_cast<float>(WindowModule::width) / static_cast<float>(cols),
			static_cast<float>(WindowModule::height) / static_cast<float>(rows),
	};
	WindowModule::recalculateTileSize = false;
}
