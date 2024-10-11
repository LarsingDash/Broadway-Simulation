#ifndef INPUT_MODULE_HPP
#define INPUT_MODULE_HPP

#include <SDL.h>
#include <unordered_map>
#include <memory>
#include "../CommandHandling/Command.hpp"
#include "../CommandHandling/Commands/RewindCommand.hpp"
#include "../CommandHandling/Commands/RenderArtistsCommand.hpp"
#include "../CommandHandling/Commands/FileSelectionCommand.hpp"
#include "../CommandHandling/Commands/PlayPauseCommand.hpp"
#include "../CommandHandling/Commands/MouseInteractionCommand.hpp"
#include "../CommandHandling/Commands/FastForwardCommand.hpp"
#include "../CommandHandling/Commands/QuitCommand.hpp"


class InputModule {
    std::unordered_map<SDL_Scancode, std::unique_ptr<Command>> commands;

public:
    InputModule();
    void handleScancode(SDL_Scancode key);
};

#endif /* INPUT_MODULE_HPP */
