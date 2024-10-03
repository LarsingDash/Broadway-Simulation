//
// Created by oknor on 10/3/2024.
//

#ifndef BROADWAY_SIMULATION_TILE_HPP
#define BROADWAY_SIMULATION_TILE_HPP


#include <vector>
#include "TileState.hpp"
#include "SDL_render.h"

class Tile {
public:
    TileState* currentState;
    std::vector<Tile*> neighbors;

    Tile(TileState* initialState) : currentState(initialState) {}

    void setState(TileState* newState) {
        currentState = newState;
    }

    void render(SDL_Renderer* renderer, int x, int y, int tileSize) {
        SDL_Rect tileRect = { x, y, tileSize, tileSize };
        SDL_SetRenderDrawColor(renderer, currentState->color.r, currentState->color.g, currentState->color.b, currentState->color.a);
        SDL_RenderFillRect(renderer, &tileRect);
    }

    void addNeighbor(Tile* neighbor) {
        neighbors.push_back(neighbor);
    }
};



#endif //BROADWAY_SIMULATION_TILE_HPP
