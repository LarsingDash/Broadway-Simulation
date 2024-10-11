#ifndef SIMULATION_MANAGER_HPP
#define SIMULATION_MANAGER_HPP

#include "Modules/WindowModule.hpp"
#include "Modules/RenderingModule.hpp"
#include "Tiles/Museum.hpp"
#include <memory>

class InputModule;

class SimulationManager {
public:
    static SimulationManager& getInstance();

    void run();
    void interactTileAtMouse();
    static std::unique_ptr<Museum> museum;

    bool shouldQuit;
private:
    SimulationManager();
    ~SimulationManager();

    SimulationManager(const SimulationManager&) = delete;
    SimulationManager& operator=(const SimulationManager&) = delete;

    void processEvents();

    std::unique_ptr<WindowModule> windowModule;
    std::unique_ptr<RenderingModule> renderingModule;
    std::unique_ptr<InputModule> inputModule;
};

#endif /* SIMULATION_MANAGER_HPP */