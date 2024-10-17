//
// Created by 11896 on 11/10/2024.
//

#ifndef BROADWAY_SIMULATION_TILEINTERACTIONCOMMAND_HPP
#define BROADWAY_SIMULATION_TILEINTERACTIONCOMMAND_HPP

#include <iostream>
#include "../Command.hpp"

class TileInteractionCommand : public Command {
	public:
		void execute() override;
};

#endif //BROADWAY_SIMULATION_TILEINTERACTIONCOMMAND_HPP
