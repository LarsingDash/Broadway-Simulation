//
// Created by 11896 on 11/10/2024.
//

#ifndef BROADWAY_SIMULATION_RENDERARTISTSCOMMAND_HPP
#define BROADWAY_SIMULATION_RENDERARTISTSCOMMAND_HPP

#include "../Command.hpp"
#include <iostream>

class RenderArtistsCommand : public Command {
	public:
		void execute() override;
};

#endif //BROADWAY_SIMULATION_RENDERARTISTSCOMMAND_HPP
