#include <iostream>
#include <SDL.h>

SDL_Window* window;
SDL_Renderer* renderer;

int windowWidth = 800;
int windowHeight = 600;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Couldn't Init video: " << SDL_GetError() << std::endl;
		return 1;
	}
	//Create window
	window = SDL_CreateWindow("SDLTest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							  windowWidth, windowHeight,
							  SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cerr << "Couldn't create window: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	//Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		std::cerr << "Couldn't create renderer: " << SDL_GetError() << std::endl;
		SDL_Quit();
		SDL_DestroyWindow(window);
		return 1;
	}
	std::cout << "Hello, World!" << std::endl;
	return 0;
}
