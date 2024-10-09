#ifndef BROADWAY_SIMULATION_TILESTATE_HPP
#define BROADWAY_SIMULATION_TILESTATE_HPP

#include <iostream>
#include "SDL_pixels.h"

class TileState {
public:
    TileState(SDL_Color color, float weight) : color{color}, weight{weight} {};
	virtual ~TileState() = default;
	
    virtual void handleInteraction() = 0;

    virtual void logTileData() {
        std::cout << "Tile clicked: Weight=" << weight << ", Color (RGBA): "
                  << static_cast<int>(color.r) << ", "
                  << static_cast<int>(color.g) << ", "
                  << static_cast<int>(color.b) << ", "
                  << static_cast<int>(color.a) << ", Type: " << typeid(*this).name() << std::endl;
    }

    SDL_Color color;
    float weight;
};

#endif // BROADWAY_SIMULATION_TILESTATE_HPP
