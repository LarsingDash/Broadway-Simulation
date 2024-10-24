//
// Created by 11896 on 23/10/2024.
//

#include "MementoManager.hpp"
#include "../Tiles/MuseumBuilder.hpp"

MementoManager::MementoManager(Museum& museum, ArtistsManager& artistsManager)
        : museum(museum),
          artistsManager(artistsManager),
          careTaker(std::make_unique<CareTaker>()) {
}


void MementoManager::saveState() {
    if (!careTaker) return;

    std::vector<std::vector<Memento::TileState>> tileStates;
    tileStates.reserve(museum.getRows());

    for (int y = 0; y < museum.getRows(); ++y) {
        std::vector<Memento::TileState> row;
        row.reserve(museum.getCols());

        for (int x = 0; x < museum.getCols(); ++x) {
            const Tile& tile = museum.getTile(x, y);
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
    for (const auto& artist : artistsManager.getArtists()) {
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

void MementoManager::undo() {
    if (Memento *memento = careTaker->undo()) {
        restoreState(memento);
    }
}

void MementoManager::redo() {
    if (Memento *memento = careTaker->redo()) {
        restoreState(memento);
    }
}

void MementoManager::restoreState(Memento *memento) const {
    MuseumBuilder builder(static_cast<int>(memento->tileStates.size()), static_cast<int>(memento->tileStates[0].size()));
    builder.withAutoNeighbors();

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

    for (int y = 0; y < museum.getRows(); ++y) {
        for (int x = 0; x < museum.getCols(); ++x) {
            TileState& state = *museum.getTile(x, y).currentState;
            state.interactionCount = memento->tileStates[y][x].interactionCount;
        }
    }

    artistsManager.clearArtists();
    for (const auto &state: memento->artistStates) {
        artistsManager.addArtist(glm::ivec2(state.lastTile), state.direction);
        auto &artist = artistsManager.getArtists().back();
        artist->setPosition(state.position);
        if (state.markedForDeletion) {
            artist->markForDeletion();
        }
    }
}




