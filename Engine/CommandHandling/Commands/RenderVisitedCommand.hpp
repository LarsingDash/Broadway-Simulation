//
// Created by larsv on 24/10/2024.
//

#ifndef BROADWAY_SIMULATION_RENDERVISITEDCOMMAND_HPP
#define BROADWAY_SIMULATION_RENDERVISITEDCOMMAND_HPP

#include "../Command.hpp"

class RenderVisitedCommand : public Command {
	public:
		void execute() override;
};


#endif //BROADWAY_SIMULATION_RENDERVISITEDCOMMAND_HPP
