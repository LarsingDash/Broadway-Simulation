//
// Created by larsv on 03/10/2024.
//

#include "Blue.hpp"
#include "Yellow.hpp"


void Blue::handleInteraction(Tile* tile, bool mouseClick) {
    // Log the interaction


    const auto& neighbors = tile->getNeighbors();
    int blueCount = 0;
    for (Tile* neighbor : neighbors) {
        if (blueCount >= 2) break;

        if (neighbor->currentState->letter != 'B') {
            neighbor->setState<Blue>();
            blueCount++;
        }
    }

    tile->setState<Yellow>();
}
