#include "InputModule.hpp"
#include <iostream>

void InputModule::handleScancode(SDL_Scancode key, bool& shouldQuit) {
    if (key == SDL_SCANCODE_ESCAPE) {
        shouldQuit = true;
        std::cout << "Escape key pressed!" << std::endl;
    }
}
