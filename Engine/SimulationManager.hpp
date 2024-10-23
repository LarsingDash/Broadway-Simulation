#ifndef SIMULATION_MANAGER_HPP
#define SIMULATION_MANAGER_HPP

#include "Modules/WindowModule.hpp"
#include "Modules/RenderingModule.hpp"
#include "Tiles/Museum.hpp"
#include "Artists/ArtistsManager.hpp"
#include "Modules/GUIModule.hpp"
#include "Memento/Caretaker.hpp"
#include <memory>

class InputModule;

class SimulationManager {
public:
    static SimulationManager &getInstance();

    SimulationManager(const SimulationManager &) = delete;

    SimulationManager &operator=(const SimulationManager &) = delete;

    void saveState();
    void undo();
    void redo();
    void run();
    void setFramesPerSave(unsigned int frames) { framesPerSave = frames; }
    unsigned int getFramesPerSave() const { return framesPerSave; }
    void toggleAutoSave() { autoSaveEnabled = !autoSaveEnabled; }
    bool isAutoSaveEnabled() const { return autoSaveEnabled; }
    static const size_t MAX_SAVED_STATES = 100;
    void toggleRunning();
    bool shouldQuit;

    std::unique_ptr<Museum> museum;
    std::unique_ptr<ArtistsManager> artistsManager;
    std::unique_ptr<GUIModule> guiModule;
    std::unique_ptr<InputModule> inputModule;
private:
    static SimulationManager instance;
    bool isRunning = true;

    std::unique_ptr<CareTaker> careTaker;
    unsigned int framesSinceLastSave;
    unsigned int framesPerSave;
    bool autoSaveEnabled;
    void restoreState(Memento *memento) const;

    SimulationManager();
    ~SimulationManager();

    void processEvents();
    std::unique_ptr<WindowModule> windowModule;
    std::unique_ptr<RenderingModule> renderingModule;

};

#endif /* SIMULATION_MANAGER_HPP */