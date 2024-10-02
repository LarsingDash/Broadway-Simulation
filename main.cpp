#include <iostream>
#include <SDL.h>
#include "Engine/SimulationManager.hpp"

int main(int argc, char* argv[]) {
    SimulationManager engine;
    engine.run();
    return 0;
}