//
// Created by 11896 on 11/10/2024.
//

#ifndef BROADWAY_SIMULATION_REWINDCOMMAND_HPP
#define BROADWAY_SIMULATION_REWINDCOMMAND_HPP

#include "../Command.hpp"
#include <iostream>

class RewindCommand : public Command {
	public:
		void execute() override;
};

#endif //BROADWAY_SIMULATION_REWINDCOMMAND_HPP
