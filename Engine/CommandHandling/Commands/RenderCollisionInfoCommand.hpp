//
// Created by larsv on 24/10/2024.
//

#ifndef BROADWAY_SIMULATION_RENDERCOLLISIONINFOCOMMAND_HPP
#define BROADWAY_SIMULATION_RENDERCOLLISIONINFOCOMMAND_HPP

#include "../Command.hpp"

class RenderCollisionInfoCommand : public Command {
	public:
		void execute() override;
};


#endif //BROADWAY_SIMULATION_RENDERCOLLISIONINFOCOMMAND_HPP
