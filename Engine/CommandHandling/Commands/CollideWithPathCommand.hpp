//
// Created by larsv on 24/10/2024.
//

#ifndef BROADWAY_SIMULATION_COLLIDEWITHPATHCOMMAND_HPP
#define BROADWAY_SIMULATION_COLLIDEWITHPATHCOMMAND_HPP

#include "../Command.hpp"

class CollideWithPathCommand : public Command {
	public:
		void execute() override;
};


#endif //BROADWAY_SIMULATION_COLLIDEWITHPATHCOMMAND_HPP
