#include "SimulationManager.hpp"
#include "Modules/InputModule.hpp"
#include "FileReading/SourceStrategy/WebSourceStrategy.hpp"
#include "Tiles/MuseumBuilder.hpp"
#include <SDL_timer.h>
#include <backends/imgui_impl_sdl2.h>

SimulationManager SimulationManager::instance{};

SimulationManager &SimulationManager::getInstance() { return instance; }

SimulationManager::SimulationManager() : shouldQuit(false),
                                         framesSinceLastSave(0),
                                         framesPerSave(60),
                                         autoSaveEnabled(true) {

    windowModule = std::make_unique<WindowModule>();

    museum = std::make_unique<Museum>();
    artistsManager = std::make_unique<ArtistsManager>();

    renderingModule = std::make_unique<RenderingModule>(windowModule->getWindow());
    inputModule = std::make_unique<InputModule>();
    guiModule = std::make_unique<GUIModule>(windowModule->getWindow(), renderingModule->getRenderer(), *inputModule);
    careTaker = std::make_unique<CareTaker>();

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

        if (isRunning){
            SimulationManager::artistsManager->update(*museum, static_cast<float>(delta) / 1000.f);
            if (autoSaveEnabled) {
                framesSinceLastSave++;
                if (framesSinceLastSave >= framesPerSave) {
                    saveState();
                    framesSinceLastSave = 0;
                }
            }
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

void SimulationManager::saveState() {


    if (!careTaker) return;

    std::vector<std::vector<Memento::TileState>> tileStates;
    tileStates.reserve(museum->getRows());

    // Save tile states
    for (int y = 0; y < museum->getRows(); ++y) {
        std::vector<Memento::TileState> row;
        row.reserve(museum->getCols());

        for (int x = 0; x < museum->getCols(); ++x) {
            const Tile& tile = museum->getTile(x, y);
            Memento::TileState state{
                    tile.currentState->letter,
                    tile.getPos(),
                    tile.currentState->config.first,
                    tile.currentState->config.second,
                    tile.currentState->interactionCount
            };
            row.push_back(state);
        }
        tileStates.push_back(std::move(row));
    }

    std::vector<Memento::ArtistState> artistStates;
    for (const auto& artist : artistsManager->getArtists()) {
        Memento::ArtistState state{
                artist->getPosition(),
                artist->getDirection(),
                artist->getLastTile(),
                artist->isMarkedForDeletion()
        };
        artistStates.push_back(state);
    }

    careTaker->addMemento(std::make_unique<Memento>(tileStates, artistStates));

    while (careTaker->getStateCount() > MAX_SAVED_STATES) {
        careTaker->removeOldestState();
    }
}

void SimulationManager::undo() {
    if (Memento *memento = careTaker->undo()) {
        restoreState(memento);
    }
}

void SimulationManager::redo() {
    if (Memento *memento = careTaker->redo()) {
        restoreState(memento);
    }
}

void SimulationManager::restoreState(Memento *memento) {
    MuseumBuilder builder(memento->tileStates.size(), memento->tileStates[0].size());

    for (const auto& row : memento->tileStates) {
        for (const auto& state : row) {
            if (!builder.hasColor(state.letter)) {
                builder.addColor(state.letter, {state.color, state.weight});
            }
        }
    }

    for (size_t y = 0; y < memento->tileStates.size(); ++y) {
        for (size_t x = 0; x < memento->tileStates[y].size(); ++x) {
            const auto &state = memento->tileStates[y][x];
            builder.addTile({x, y}, state.letter);
        }
    }

    builder.finish();

    artistsManager->clearArtists();
    for (const auto &state: memento->artistStates) {
        artistsManager->addArtist(
                glm::ivec2(state.lastTile),
                state.direction
        );
        auto &artist = artistsManager->getArtists().back();
        artist->setPosition(state.position);
        if (state.markedForDeletion) {
            artist->markForDeletion();
        }
    }
}

void SimulationManager::toggleRunning() { isRunning = !isRunning; }