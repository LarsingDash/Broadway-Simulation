#include "WindowModule.hpp"
#include <iostream>

WindowModule::WindowModule() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Couldn't init video: " << SDL_GetError() << std::endl;
		return;
	}

	window = SDL_CreateWindow("SDLTest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							 600, 600, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cerr << "Couldn't create window: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}
}

WindowModule::~WindowModule() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}

SDL_Window* WindowModule::getWindow() {
	return window;
}
