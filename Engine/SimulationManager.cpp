#include "SimulationManager.hpp"
#include "Tiles/TileStates/Blue.hpp"
#include "Tiles/TileStates/White.hpp"
#include "FileReading/SourceStrategy/WebSourceStrategy.hpp"
#include <iostream>

SimulationManager::SimulationManager() : shouldQuit(false) {
    windowModule = std::make_unique<WindowModule>();
    museum = std::make_unique<Museum>(30, 30, 20, new White());

    renderingModule = std::make_unique<RenderingModule>(windowModule->getWindow(), museum.get());
    inputModule = std::make_unique<InputModule>();


    museum->setNeighbors();
}

SimulationManager::~SimulationManager() {
	WebSourceStrategy::cleanup();
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
            int x, y;
            SDL_GetMouseState(&x, &y);

            int tileX = x / 20;
            int tileY = y / 20;

            if (tileX >= 0 && tileX < museum->getCols() && tileY >= 0 && tileY < museum->getRows()) {
                Tile& clickedTile = museum->getTile(tileY, tileX);
                clickedTile.currentState->logTileData();
                clickedTile.currentState->handleInteraction();
            }

            std::cout << "Clicked tile at: " << tileX << " - " << tileY << std::endl;
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
//            std::cout << "FPS: " << frameCount << std::endl;
            fps = 0;
            frameCount = 0;
        }
    }
}
