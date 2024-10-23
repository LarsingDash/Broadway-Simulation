#include <SDL.h>
#include "Engine/SimulationManager.hpp"
#include "Testing.hpp"

int main(int argc, char* argv[]) {
	//If one of the arguments is "test", run the tests instead of the simulation
	for (int i = 0; i < argc; i++) {
		if (std::string(argv[i]) == "test") {
			return Testing::RunTests();
		}
	}

    SimulationManager::getInstance().run();
	return 0;
}