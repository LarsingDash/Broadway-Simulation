//
// Created by 11896 on 22/10/2024.
//

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
        currentIndex--;
        return mementos[currentIndex - 1].get();
    }
    return nullptr;
}

Memento* CareTaker::redo() {
    if (currentIndex < mementos.size()) {
        currentIndex++;
        return mementos[currentIndex - 1].get();
    }
    return nullptr;
}
