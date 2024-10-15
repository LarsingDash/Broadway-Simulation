#ifndef SIMULATION_MANAGER_HPP
#define SIMULATION_MANAGER_HPP

#include "Modules/WindowModule.hpp"
#include "Modules/RenderingModule.hpp"
#include "Modules/InputModule.hpp"
#include "Tiles/Museum.hpp"
#include "Artists/ArtistsManager.hpp"
#include <memory>

class SimulationManager {
public:
    SimulationManager();
    ~SimulationManager();
    void run();

    static std::unique_ptr<Museum> museum;
    static std::unique_ptr<ArtistsManager> artistsManager;
private:
    void processEvents();

    bool shouldQuit;

    std::unique_ptr<WindowModule> windowModule;
    std::unique_ptr<RenderingModule> renderingModule;
    std::unique_ptr<InputModule> inputModule;
};

#endif /* SIMULATION_MANAGER_HPP */
