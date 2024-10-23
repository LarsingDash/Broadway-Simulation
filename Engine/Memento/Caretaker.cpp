//
// Created by 11896 on 22/10/2024.
//

#include <iostream>
#include "CareTaker.hpp"

CareTaker::CareTaker() : currentIndex(0) {}

size_t CareTaker::getStateCount() const {
    return mementos.size();
}

void CareTaker::removeOldestState() {
    if (!mementos.empty()) {
        mementos.erase(mementos.begin());
        if (currentIndex > 0) currentIndex--;
    }
}

void CareTaker::addMemento(std::unique_ptr<Memento> memento) {
    if (currentIndex < mementos.size()) {
        mementos.erase(mementos.begin() + currentIndex, mementos.end());
    }
    mementos.push_back(std::move(memento));
    currentIndex = mementos.size();
}


Memento* CareTaker::undo() {
    if (currentIndex > 0) {
        std::cout << "Undoing" << std::endl;
        currentIndex--;
        return mementos[currentIndex].get();
    }
    std::cout << "Cannot undo" << std::endl;
    return nullptr;
}

Memento* CareTaker::redo() {
    if (currentIndex < mementos.size()) {
        std::cout << "Redoing" << std::endl;
        return mementos[currentIndex++].get();
    }
    std::cout << "Cannot redo" << std::endl;
    return nullptr;
}
