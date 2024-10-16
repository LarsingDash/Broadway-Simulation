#include <SDL.h>
#include "Engine/SimulationManager.hpp"

int main(int argc, char* argv[]) {
    SimulationManager::getInstance().run();
    return 0;
}