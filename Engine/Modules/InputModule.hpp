#ifndef INPUT_MODULE_HPP
#define INPUT_MODULE_HPP

#include <unordered_map>
#include <memory>
#include <SDL_scancode.h>
#include "../CommandHandling/Command.hpp"

class InputModule {
		std::unordered_map<SDL_Scancode, std::unique_ptr<Command>> commands;

	public:
		InputModule();
        void handleScancode(SDL_Scancode key);
		void handleMouseClick();

};

#endif /* INPUT_MODULE_HPP */
