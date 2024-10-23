//
// Created by 11896 on 23/10/2024.
//

#ifndef BROADWAY_SIMULATION_MEMENTOMANAGER_HPP
#define BROADWAY_SIMULATION_MEMENTOMANAGER_HPP


#include "../Tiles/Museum.hpp"
#include "../Artists/ArtistsManager.hpp"
#include "Memento.hpp"
#include "Caretaker.hpp"

class MementoManager {
public:
    MementoManager(Museum* museum, ArtistsManager* artistsManager);


    void saveState();
    void undo();
    void redo();



private:
    void restoreState(Memento* memento) const;
    static const size_t MAX_SAVED_STATES = 100;
    Museum* museum;
    ArtistsManager* artistsManager;
    std::unique_ptr<CareTaker> careTaker;
};



#endif //BROADWAY_SIMULATION_MEMENTOMANAGER_HPP
