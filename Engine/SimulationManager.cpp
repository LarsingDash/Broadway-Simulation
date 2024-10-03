#include "SimulationManager.hpp"
#include <iostream>

SimulationManager::SimulationManager() : shouldQuit(false) {
    windowModule = std::make_unique<WindowModule>();
    renderingModule = std::make_unique<RenderingModule>(windowModule->getWindow());
    inputModule = std::make_unique<InputModule>();
}

void SimulationManager::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            shouldQuit = true;
        } else if (event.type == SDL_KEYDOWN) {
			inputModule->handleScancode(event.key.keysym.scancode, shouldQuit);
        }

		if (event.type == SDL_MOUSEBUTTONDOWN) {
			int x;
			int y;
			SDL_GetMouseState(&x, &y);
			
			x /= 20;
			y /= 20;
			
			std::cout << x << " - " << y << std::endl;
		}
    }
}

void SimulationManager::run() {
    Uint32 prevTicks = SDL_GetTicks();
    Uint32 fpsInterval = 1000;
    Uint32 fps = 0, frameCount = 0;

    while (!shouldQuit) {
        Uint32 curTicks = SDL_GetTicks();
        Uint32 delta = curTicks - prevTicks;
        prevTicks = curTicks;

        processEvents();
        renderingModule->clear();
		
//		artistManager->update(static_cast<float>(delta) / 1000.f));
        renderingModule->draw();
		
		renderingModule->present();

        frameCount++;
        fps += delta;
        if (fps >= fpsInterval) {
            std::cout << "FPS: " << frameCount << std::endl;
            fps = 0;
            frameCount = 0;
        }
    }
}
