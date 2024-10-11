#include "InputModule.hpp"
#include "../FileReading/FileReaderTemplate.hpp"
#include <iostream>

InputModule::InputModule() {
    commands[SDL_SCANCODE_SPACE] = std::make_unique<PlayPauseCommand>();
    commands[SDL_SCANCODE_RETURN] = std::make_unique<MouseInteractionCommand>();
    commands[SDL_SCANCODE_O] = std::make_unique<FileSelectionCommand>();
    commands[SDL_SCANCODE_A] = std::make_unique<RenderArtistsCommand>();
    commands[SDL_SCANCODE_LEFT] = std::make_unique<RewindCommand>();
    commands[SDL_SCANCODE_RIGHT] = std::make_unique<FastForwardCommand>();
}

void InputModule::handleScancode(SDL_Scancode key, bool& shouldQuit) {
	switch (key) {
		default:
			break;
		case SDL_SCANCODE_ESCAPE:
			shouldQuit = true;
			std::cout << "Escape key pressed!" << std::endl;
			break;

	}
    auto it = commands.find(key);
    if (it != commands.end()) {
        it->second->execute();
    }
}
