#pragma once

#include "WindowModule.h"
#include "RenderingModule.h"
#include "InputModule.h"

class SimulationManager {
public:
    SimulationManager();
    ~SimulationManager();
    void run();

private:
    void processEvents();

    bool shouldQuit;
    WindowModule* windowModule;
    RenderingModule* renderingModule;
    InputModule* inputModule;
};
