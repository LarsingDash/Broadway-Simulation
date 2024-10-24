#ifndef SIMULATION_MANAGER_HPP
#define SIMULATION_MANAGER_HPP

#include "Modules/WindowModule.hpp"
#include "Modules/RenderingModule.hpp"
#include "Tiles/Museum.hpp"
#include "Artists/ArtistsManager.hpp"
#include "Modules/GUIModule.hpp"
#include <memory>

class InputModule;

class SimulationManager {
	public:
		static SimulationManager& getInstance();
		
		SimulationManager(const SimulationManager&) = delete;
		SimulationManager& operator=(const SimulationManager&) = delete;
		void run();

		std::unique_ptr<Museum> museum;
		std::unique_ptr<ArtistsManager> artistsManager;
		std::unique_ptr<GUIModule> guiModule;
		std::unique_ptr<InputModule> inputModule;
		std::unique_ptr<RenderingModule> renderingModule;

		void toggleRunning();
		bool shouldQuit;
	private:
		static SimulationManager instance;
		bool isRunning = false;
	private:
		SimulationManager();
		~SimulationManager();

		void processEvents();
		std::unique_ptr<WindowModule> windowModule;
};

#endif /* SIMULATION_MANAGER_HPP */