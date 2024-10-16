#ifndef SIMULATION_MANAGER_HPP
#define SIMULATION_MANAGER_HPP

#include "Modules/WindowModule.hpp"
#include "Modules/RenderingModule.hpp"
#include "Tiles/Museum.hpp"
#include "Artists/ArtistsManager.hpp"
#include <memory>

class InputModule;

class SimulationManager {
	public:
		static SimulationManager& getInstance();

		SimulationManager(const SimulationManager&) = delete;
		SimulationManager& operator=(const SimulationManager&) = delete;

		void run();
		void interactTileAtMouse() const;

		bool shouldQuit;
		
		std::unique_ptr<Museum> museum;
		std::unique_ptr<ArtistsManager> artistsManager;
	private:
		static SimulationManager instance;
		
		SimulationManager();
		~SimulationManager();

		void processEvents();

		std::unique_ptr<WindowModule> windowModule;
		std::unique_ptr<RenderingModule> renderingModule;
		std::unique_ptr<InputModule> inputModule;
};

#endif /* SIMULATION_MANAGER_HPP */