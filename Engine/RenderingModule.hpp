#ifndef RENDERING_MODULE_HPP
#define RENDERING_MODULE_HPP

#include <SDL.h>

class RenderingModule {
public:
    explicit RenderingModule(SDL_Window* window);
    ~RenderingModule();
	void clear();
    void draw();
	void present();

private:
    SDL_Renderer* renderer;
};

#endif /* RENDERING_MODULE_HPP */
