//
// Created by 11896 on 16/10/2024.
//

#ifndef BROADWAY_SIMULATION_GUIMODULE_HPP
#define BROADWAY_SIMULATION_GUIMODULE_HPP

#include "backends/imgui_impl_sdl2.h"

#include "backends/imgui_impl_sdlrenderer2.h"
#include "imgui.h"
#include "SDL_render.h"



class GUIModule {
public:
    GUIModule(SDL_Window* window, SDL_Renderer* renderer);
    ~GUIModule();

    void beginFrame();
    void render();
    void shutdown();
    void toggleFileSelectionWindow();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool showFileSelectionWindow = false;

    void openFileDialog();
};


#endif //BROADWAY_SIMULATION_GUIMODULE_HPP
