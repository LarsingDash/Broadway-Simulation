#ifndef BROADWAY_SIMULATION_MUSEUM_HPP
#define BROADWAY_SIMULATION_MUSEUM_HPP

#include <vector>
#include <random>
#include "SDL_render.h"
#include "TileState.hpp"
#include "Tile.hpp"
#include "TileStates/White.hpp"
#include "TileStates/Blue.hpp"
#include "TileStates/Grey.hpp"
#include "TileStates/Red.hpp"
#include "TileStates/Yellow.hpp"

class Museum {
private:
    std::vector<std::vector<Tile>> grid;
    int rows, cols;
    int tileSize;

public:
    Museum(int rows, int cols, int tileSize, TileState* defaultState);

    void initializeRandomTiles();
    void render(SDL_Renderer* renderer);
    void setNeighbors();
    int getRows() const;
    int getCols() const;
    Tile& getTile(int row, int col);
};

#endif // BROADWAY_SIMULATION_MUSEUM_HPP
