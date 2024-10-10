#include "SimulationManager.hpp"
#include "FileReading/SourceStrategy/WebSourceStrategy.hpp"
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"
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
                clickedTile.currentState->handleInteraction(&clickedTile, true);
            }
		}
	}
}

void SimulationManager::run() {
	Uint32 prevTicks = SDL_GetTicks();
	Uint32 fpsInterval = 1000;
	Uint32 fps = 0, frameCount = 0;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(windowModule->getWindow(), renderingModule->getRenderer());
    ImGui_ImplSDLRenderer2_Init(renderingModule->getRenderer());


    while (!shouldQuit) {
        Uint32 curTicks = SDL_GetTicks();
        Uint32 delta = curTicks - prevTicks;
        prevTicks = curTicks;

        processEvents();

        ImGui_ImplSDL2_NewFrame();
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Test Venster");
        ImGui::Text("Yello!");
        ImGui::End();

        renderingModule->clear();

        renderingModule->draw();

        ImGui::Render();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderingModule->getRenderer());

        renderingModule->present();

        frameCount++;
        fps += delta;
        if (fps >= fpsInterval) {
            fps = 0;
            frameCount = 0;
        }
    }
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}
