//
// Created by oknor on 10/3/2024.
//

#ifndef BROADWAY_SIMULATION_TILE_HPP
#define BROADWAY_SIMULATION_TILE_HPP

#include "TileStates/TileState.hpp"
#include <vector>
#include <memory>
class TileState;
class Tile {
public:
    std::unique_ptr<TileState> currentState;
    std::vector<Tile*> neighbors;
    int interactionCount;
    Tile() : currentState{nullptr} {}

    template<class T>
    void setState() {
        currentState = std::make_unique<T>();
    }

    void handleInteraction(bool mouseClick);
    void addNeighbor(Tile* neighbor);
};


#endif //BROADWAY_SIMULATION_TILE_HPP
