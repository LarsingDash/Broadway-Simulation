#include <SDL.h>
#include "Engine/SimulationManager.hpp"
#include "Testing.hpp"

int main(int argc, char* argv[]) {
	for (int i = 0; i < argc; i++) {
		if (std::string(argv[i]) == "test") {
			return Testing::RunTests();
		}
	}

    SimulationManager::getInstance().run();
	return 0;
}