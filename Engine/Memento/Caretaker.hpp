#ifndef BROADWAY_SIMULATION_CARETAKER_HPP
#define BROADWAY_SIMULATION_CARETAKER_HPP

#include <vector>
#include <memory>
#include "Memento.hpp"

class CareTaker {
private:
    std::vector<std::unique_ptr<Memento>> mementos;
    size_t currentIndex;

public:
    CareTaker();

    size_t getStateCount() const;

    void removeOldestState();

    void addMemento(std::unique_ptr<Memento> memento);

    Memento* undo();

    Memento* redo();
};

#endif // BROADWAY_SIMULATION_CARETAKER_HPP
