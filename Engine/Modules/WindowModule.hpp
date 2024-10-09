#ifndef WINDOW_MODULE_HPP
#define WINDOW_MODULE_HPP

#include <SDL.h>

class WindowModule {
	public:
		WindowModule();
		~WindowModule();
		SDL_Window* getWindow();
		static void handleResize(const SDL_WindowEvent& event);
		
		static bool recalculateTileSize;
		static int width, height;
	private:
		SDL_Window* window;
};

#endif /* WINDOW_MODULE_HPP */
