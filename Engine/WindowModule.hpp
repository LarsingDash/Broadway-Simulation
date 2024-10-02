#ifndef WINDOW_MODULE_HPP
#define WINDOW_MODULE_HPP

#include <SDL.h>
#include <memory>

class WindowModule {
	public:
		WindowModule();
		~WindowModule();
		SDL_Window* getWindow();

	private:
		SDL_Window* window;
};

#endif /* WINDOW_MODULE_HPP */
