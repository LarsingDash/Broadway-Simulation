#pragma once

#include "WindowModule.h"
#include "RenderingModule.h"
#include "InputModule.h"

class Application {
public:
    Application();
    ~Application();
    void run();

private:
    void processEvents();

    bool shouldQuit;
    WindowModule* windowModule;
    RenderingModule* renderingModule;
    InputModule* inputModule;
};
