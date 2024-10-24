#ifndef INPUT_MODULE_HPP
#define INPUT_MODULE_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <SDL_scancode.h>
#include "../CommandHandling/Command.hpp"

class InputModule {
	public:
		enum Commands {
			PlayPause,
			FileSelection,
			RenderCollisionInfo,
			RenderArtists,
			CollideWithPath,
			RenderPath,
			RenderVisited,
			Quit,
			Info,
		};

		InputModule();
		void handleScancode(SDL_Scancode key);
		static void handleMouseClick(bool isLeft);
		std::unordered_map<Commands, std::pair<SDL_Scancode, std::string>> keys;

	private:
		std::unordered_map<Commands, std::unique_ptr<Command>> commandBindings{};

};

#endif /* INPUT_MODULE_HPP */
