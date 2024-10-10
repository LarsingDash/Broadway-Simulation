#include "Museum.hpp"
#include "../Modules/WindowModule.hpp"

std::unordered_map<char, std::pair<SDL_Color, float>> Museum::colors;

Museum::Museum(int rows, int cols, int tileSize)
		: rows(rows), cols(cols), tileSize(tileSize) {
	//Initialize rows
	grid = std::vector<std::vector<std::unique_ptr<Tile>>>(rows);

	for (int i = 0; i < rows; i++) {
		//Initialize columns
		grid[i] = std::vector<std::unique_ptr<Tile>>(cols);

		for (int j = 0; j < cols; j++) {
			//Initialize default builderTiles	
			(grid[i][j] = std::make_unique<Tile>())->setState<White>();
		}
	}

	//Add default color for blank (white) tiles
	Museum::colors['W'] = {SDL_Color{255, 255, 255}, 1};

//	initializeRandomTiles();
}

void Museum::initializeRandomTiles() {
	//Initialize Colors
	Museum::colors['R'] = {SDL_Color{255, 0, 0}, 1};
	Museum::colors['B'] = {SDL_Color{0, 0, 255}, 1};
	Museum::colors['Y'] = {SDL_Color{255, 255, 0}, 1};
	Museum::colors['G'] = {SDL_Color{150, 150, 150}, 1};
	Museum::colors['W'] = {SDL_Color{255, 255, 255}, 1};

	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0, 4);

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			int randomTile = distr(eng);
			switch (randomTile) {
				default:
					break;
				case 0:
					(grid[i][j] = std::make_unique<Tile>())->setState<White>();
					break;
				case 1:
					(grid[i][j] = std::make_unique<Tile>())->setState<Blue>();
					break;
				case 2:
					(grid[i][j] = std::make_unique<Tile>())->setState<Grey>();
					break;
				case 3:
					(grid[i][j] = std::make_unique<Tile>())->setState<Red>();
					break;
				case 4:
					(grid[i][j] = std::make_unique<Tile>())->setState<Yellow>();
					break;
			}
		}
	}
}

void Museum::render(SDL_Renderer* renderer) {
	if (WindowModule::recalculateTileSize) _recalculateTileSize();

	for (int x = 0; x < cols; ++x) {
		for (int y = 0; y < rows; ++y) {
			grid[x][y]->currentState->render(
					renderer,
					static_cast<float>(x) * tileSize.x,
					static_cast<float>(y) * tileSize.y,
					tileSize
			);
		}
	}
}

void Museum::setNeighbors() {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (i > 0) grid[i][j]->addNeighbor(grid[i - 1][j].get());
			if (i < rows - 1) grid[i][j]->addNeighbor(grid[i + 1][j].get());
			if (j > 0) grid[i][j]->addNeighbor(grid[i][j - 1].get());
			if (j < cols - 1) grid[i][j]->addNeighbor(grid[i][j + 1].get());
		}
	}
}

int Museum::getRows() const { return rows; }

int Museum::getCols() const { return cols; }

glm::vec2 Museum::getTileSize() const { return tileSize; }

void Museum::setRows(int row) {
	rows = row;
	_recalculateTileSize();
}

void Museum::setCols(int col) {
	cols = col;
	_recalculateTileSize();
}

Tile& Museum::getTile(int row, int col) { return *grid[row][col]; }

void Museum::setTiles(std::vector<std::vector<std::unique_ptr<Tile>>>&& tiles) { grid = std::move(tiles); }

void Museum::_recalculateTileSize() {
	tileSize = glm::vec2{
			static_cast<float>(WindowModule::width) / static_cast<float>(cols),
			static_cast<float>(WindowModule::height) / static_cast<float>(rows),
	};
	WindowModule::recalculateTileSize = false;
}
