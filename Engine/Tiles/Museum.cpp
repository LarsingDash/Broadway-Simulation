#include "Museum.hpp"

Museum::Museum(int rows, int cols, int tileSize, TileState* defaultState)
        : rows(rows), cols(cols), tileSize(tileSize) {
    grid.resize(rows, std::vector<Tile>(cols, Tile(defaultState)));
    initializeRandomTiles();
}

void Museum::initializeRandomTiles() {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, 4);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int randomTile = distr(eng);
            switch (randomTile) {
                case 0:
                    grid[i][j] = Tile(new White());
                    break;
                case 1:
                    grid[i][j] = Tile(new Blue());
                    break;
                case 2:
                    grid[i][j] = Tile(new Grey());
                    break;
                case 3:
                    grid[i][j] = Tile(new Red());
                    break;
                case 4:
                    grid[i][j] = Tile(new Yellow());
                    break;
            }
        }
    }
}

void Museum::render(SDL_Renderer* renderer) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j].render(renderer, j * tileSize, i * tileSize, tileSize);
        }
    }
}

void Museum::setNeighbors() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i > 0) grid[i][j].addNeighbor(&grid[i-1][j]);
            if (i < rows - 1) grid[i][j].addNeighbor(&grid[i+1][j]);
            if (j > 0) grid[i][j].addNeighbor(&grid[i][j-1]);
            if (j < cols - 1) grid[i][j].addNeighbor(&grid[i][j+1]);
        }
    }
}

int Museum::getRows() const {
    return rows;
}

int Museum::getCols() const {
    return cols;
}

Tile& Museum::getTile(int row, int col) {
    return grid[row][col];
}
