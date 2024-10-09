#include "WindowModule.hpp"
#include <iostream>

bool WindowModule::recalculateTileSize;
int WindowModule::width, WindowModule::height;

WindowModule::WindowModule() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Couldn't init video: " << SDL_GetError() << std::endl;
		return;
	}
	
	width = height = 600;

	window = SDL_CreateWindow("SDLTest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							  width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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

void WindowModule::handleResize(const SDL_WindowEvent& event) {
	WindowModule::width = event.data1;
	WindowModule::height = event.data2;
	WindowModule::recalculateTileSize = true;
}
