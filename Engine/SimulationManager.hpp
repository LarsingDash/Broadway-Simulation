#ifndef SIMULATION_MANAGER_HPP
#define SIMULATION_MANAGER_HPP

#include "WindowModule.hpp"
#include "RenderingModule.hpp"
#include "InputModule.hpp"
#include <memory>

class SimulationManager {
public:
    SimulationManager();
    ~SimulationManager() = default;
    void run();

private:
    void processEvents();

    bool shouldQuit;
	
    std::unique_ptr<WindowModule> windowModule;
    std::unique_ptr<RenderingModule> renderingModule;
    std::unique_ptr<InputModule> inputModule;
};

#endif /* SIMULATION_MANAGER_HPP */
