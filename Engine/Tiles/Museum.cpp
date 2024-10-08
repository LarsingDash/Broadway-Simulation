#include "Museum.hpp"

Museum::Museum(int rows, int cols, int tileSize)
		: rows(rows), cols(cols), tileSize(tileSize) {
	//Initialize rows
	grid = std::vector<std::vector<std::unique_ptr<Tile>>>(rows);
	
	for (int i = 0; i < rows; i++) {
		//Initialize columns
		grid[i] = std::vector<std::unique_ptr<Tile>>(cols);
		
		for (int j = 0; j < cols; j++) {
			//Initialize default tiles	
			(grid[i][j] = std::make_unique<Tile>())->setState<White>();
		}
	}
}

void Museum::initializeRandomTiles() {
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
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			grid[i][j]->render(renderer, j * tileSize, i * tileSize, tileSize);
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

void Museum::setRows(int row) { rows = row; }

void Museum::setCols(int col) { cols = col; }

Tile& Museum::getTile(int row, int col) { return *grid[row][col]; }

void Museum::setTiles(std::vector<std::vector<std::unique_ptr<Tile>>>&& tiles) { grid = std::move(tiles); }
