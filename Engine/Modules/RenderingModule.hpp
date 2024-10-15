#ifndef RENDERING_MODULE_HPP
#define RENDERING_MODULE_HPP

#include "../Tiles/Museum.hpp"
#include "../Artists/ArtistsManager.hpp"
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
    Museum* museum;
    ArtistsManager* artistsManager;
};

#endif /* RENDERING_MODULE_HPP */
