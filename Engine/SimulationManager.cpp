#include "SimulationManager.hpp"
#include "Modules/InputModule.hpp"
#include "FileReading/SourceStrategy/WebSourceStrategy.hpp"
#include <SDL_timer.h>
#include <backends/imgui_impl_sdl2.h>

SimulationManager SimulationManager::instance{};

SimulationManager& SimulationManager::getInstance() { return instance; }

SimulationManager::SimulationManager() : shouldQuit(false) {
	windowModule = std::make_unique<WindowModule>();

	museum = std::make_unique<Museum>();
	artistsManager = std::make_unique<ArtistsManager>();

	renderingModule = std::make_unique<RenderingModule>(windowModule->getWindow());
	inputModule = std::make_unique<InputModule>();
	guiModule = std::make_unique<GUIModule>(windowModule->getWindow(), renderingModule->getRenderer(), *inputModule);
	
	pathfindingModule = std::make_unique<PathfindingModule>(*museum);
	collisionModule = std::make_unique<CollisionModule>(*artistsManager, *pathfindingModule, *renderingModule);
}

SimulationManager::~SimulationManager() {
	WebSourceStrategy::cleanup();
	guiModule->shutdown();
}

void SimulationManager::processEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		ImGui_ImplSDL2_ProcessEvent(&event);

		switch (event.type) {
			default:
				break;
			case SDL_QUIT:
				shouldQuit = true;
				break;
			case SDL_KEYDOWN:
				inputModule->handleScancode(event.key.keysym.scancode);
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
					WindowModule::handleResize(event.window);
				break;
			case SDL_MOUSEBUTTONDOWN:
				inputModule->handleMouseClick();
				break;

		}
	}
}

void SimulationManager::run() {
	//FPS Prep
	Uint32 prevTicks = SDL_GetTicks();
	Uint32 fpsInterval = 1000;
	Uint32 fps = 0, frameCount = 0;

	while (!shouldQuit) {
		//New FPS
		Uint32 curTicks = SDL_GetTicks();
		Uint32 delta = curTicks - prevTicks;
		prevTicks = curTicks;

		//Events
		processEvents();

		//Cycle
		GUIModule::beginFrame();
		renderingModule->clear();

		if (isRunning) {
			artistsManager->update(static_cast<float>(delta) / 1000.f);
			collisionModule->update();
		}

		renderingModule->draw();
		guiModule->render();

		renderingModule->present();

		//FPS cycle
		frameCount++;
		fps += delta;
		if (fps >= fpsInterval) {
			std::cout << "FPS: " << frameCount << std::endl;
			fps = 0;
			frameCount = 0;
		}
	}
}

void SimulationManager::toggleRunning() {
	if (!artistsManager->getArtists().empty()) {
		isRunning = !isRunning;
	}
}
