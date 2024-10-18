#ifndef INPUT_MODULE_HPP
#define INPUT_MODULE_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <SDL_scancode.h>
#include "../CommandHandling/Command.hpp"

class InputModule {
	public:
		InputModule();
        void handleScancode(SDL_Scancode key);
		void handleMouseClick();
	private:
		enum Commands {
			PlayPause,
			TileInteraction,
			FileSelection,
			RenderArtists,
			Rewind,
			FastForward,
			Quit,
			Info,
		};
		
		std::unordered_map<Commands, SDL_Scancode> keys;
		std::unordered_map<Commands, std::unique_ptr<Command>> commandBindings{};

};

#endif /* INPUT_MODULE_HPP */
