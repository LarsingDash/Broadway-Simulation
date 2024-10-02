#ifndef INPUT_MODULE_HPP
#define INPUT_MODULE_HPP

#include <SDL.h>

class InputModule {
public:
    void handleScancode(SDL_Scancode key, bool& shouldQuit);
};

#endif /* INPUT_MODULE_HPP */
