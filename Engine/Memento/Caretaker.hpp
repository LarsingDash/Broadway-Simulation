#ifndef BROADWAY_SIMULATION_CARETAKER_HPP
#define BROADWAY_SIMULATION_CARETAKER_HPP

#include <vector>
#include <memory>
#include "Memento.hpp"

class CareTaker {
	public:
		CareTaker();

		[[nodiscard]] size_t getStateCount() const;
		void removeOldestState();
		void addMemento(std::unique_ptr<Memento> memento);

		Memento* undo();
		Memento* redo();
	private:
		std::vector<std::unique_ptr<Memento>> mementos;
		size_t currentIndex;
};

#endif // BROADWAY_SIMULATION_CARETAKER_HPP
