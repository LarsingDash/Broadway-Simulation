//
// Created by 11896 on 11/10/2024.
//

#ifndef BROADWAY_SIMULATION_PLAYPAUSECOMMAND_HPP
#define BROADWAY_SIMULATION_PLAYPAUSECOMMAND_HPP

#include "../Command.hpp"
#include <iostream>

class PlayPauseCommand : public Command {
	public:
		void execute() override;
};

#endif //BROADWAY_SIMULATION_PLAYPAUSECOMMAND_HPP
