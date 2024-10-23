//
// Created by larsv on 23/10/2024.
//

#ifndef BROADWAY_SIMULATION_TESTING_HPP
#define BROADWAY_SIMULATION_TESTING_HPP

#include "Engine/SimulationManager.hpp"
#include <string>

class Testing {
	public:
		static int RunTests();
	private:
		static std::string error;
		static void _fileReading(SimulationManager& simulationManager);
		static void _tileInteraction(SimulationManager& simulationManager);
		static void _artistUpdate(SimulationManager& simulationManager);
};

#endif //BROADWAY_SIMULATION_TESTING_HPP
