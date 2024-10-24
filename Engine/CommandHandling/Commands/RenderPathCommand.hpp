//
// Created by larsv on 24/10/2024.
//

#ifndef BROADWAY_SIMULATION_RENDERPATHCOMMAND_HPP
#define BROADWAY_SIMULATION_RENDERPATHCOMMAND_HPP

#include "../Command.hpp"

class RenderPathCommand : public Command {
	public:
		void execute() override;
};


#endif //BROADWAY_SIMULATION_RENDERPATHCOMMAND_HPP
