#include "SimulationManager.hpp"
#include "FileReading/SourceStrategy/WebSourceStrategy.hpp"
#include <iostream>

std::unique_ptr<Museum> SimulationManager::museum;

SimulationManager::SimulationManager() : shouldQuit(false) {
	windowModule = std::make_unique<WindowModule>();
	SimulationManager::museum = std::make_unique<Museum>();

	renderingModule = std::make_unique<RenderingModule>(windowModule->getWindow(), museum.get());
	inputModule = std::make_unique<InputModule>();
}

SimulationManager::~SimulationManager() {
	WebSourceStrategy::cleanup();
}

void SimulationManager::processEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			default:
				break;
			case SDL_QUIT:
				shouldQuit = true;
				break;
			case SDL_KEYDOWN:
				inputModule->handleScancode(event.key.keysym.scancode, shouldQuit);
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
					WindowModule::handleResize(event.window);
		}

		if (event.type == SDL_MOUSEBUTTONDOWN) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			
			glm::vec2 tileSize = museum->getTileSize();
			
			int tileX = static_cast<int>(static_cast<float>(x) / tileSize.x);
			int tileY = static_cast<int>(static_cast<float>(y) / tileSize.y);

			if (tileX >= 0 && tileX < museum->getCols() && tileY >= 0 && tileY < museum->getRows()) {
				Tile& clickedTile = museum->getTile(tileX, tileY);
				clickedTile.logTileData();
				clickedTile.currentState->handleInteraction();
			}
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
