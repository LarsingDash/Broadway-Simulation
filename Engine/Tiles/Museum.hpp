#ifndef BROADWAY_SIMULATION_MUSEUM_HPP
#define BROADWAY_SIMULATION_MUSEUM_HPP

#include <vector>
#include <unordered_map>
#include <random>
#include "SDL_render.h"
#include "TileStates/TileState.hpp"
#include "Tile.hpp"
#include "TileStates/White.hpp"
#include "TileStates/Blue.hpp"
#include "TileStates/Grey.hpp"
#include "TileStates/Red.hpp"
#include "TileStates/Yellow.hpp"

class Museum {
private:
    std::vector<std::vector<std::unique_ptr<Tile>>> grid;
    int rows, cols;
    int tileSize;

public:
    Museum(int rows, int cols, int tileSize);

    void initializeRandomTiles();
    void render(SDL_Renderer* renderer);
    void setNeighbors();
    [[nodiscard]] int getRows() const;
    [[nodiscard]] int getCols() const;
	void setRows(int rows);
	void setCols(int cols);
    Tile& getTile(int row, int col);
	void setTiles(std::vector<std::vector<std::unique_ptr<Tile>>>&& tiles);
	void setColor(const char& c, const std::pair<SDL_Color, float>&& config);
	
	static std::unordered_map<char, std::pair<SDL_Color, float>> colors;
};

#endif // BROADWAY_SIMULATION_MUSEUM_HPP
