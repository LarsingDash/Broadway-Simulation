#include "InputModule.hpp"
#include <iostream>

InputModule::InputModule(bool& shouldQuit) {
    commands[SDL_SCANCODE_SPACE] = std::make_unique<PlayPauseCommand>();
    commands[SDL_SCANCODE_RETURN] = std::make_unique<MouseInteractionCommand>();
    commands[SDL_SCANCODE_O] = std::make_unique<FileSelectionCommand>();
    commands[SDL_SCANCODE_A] = std::make_unique<RenderArtistsCommand>();
    commands[SDL_SCANCODE_LEFT] = std::make_unique<RewindCommand>();
    commands[SDL_SCANCODE_RIGHT] = std::make_unique<FastForwardCommand>();
    commands[SDL_SCANCODE_ESCAPE] = std::make_unique<QuitCommand>(shouldQuit);
}

void InputModule::handleScancode(SDL_Scancode key) {
    auto it = commands.find(key);
    if (it != commands.end()) {
        it->second->execute();
    }
}
