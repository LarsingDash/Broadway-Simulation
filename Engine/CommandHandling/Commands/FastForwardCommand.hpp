//
// Created by 11896 on 11/10/2024.
//

#ifndef BROADWAY_SIMULATION_FASTFORWARDCOMMAND_HPP
#define BROADWAY_SIMULATION_FASTFORWARDCOMMAND_HPP
#include "../../SimulationManager.hpp"

#include <iostream>
#include "../Command.hpp"

class FastForwardCommand : public Command {
	public:
		void execute() override;
};

#endif //BROADWAY_SIMULATION_FASTFORWARDCOMMAND_HPP
