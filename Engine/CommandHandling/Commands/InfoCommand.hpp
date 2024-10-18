//
// Created by larsv on 18/10/2024.
//

#ifndef BROADWAY_SIMULATION_INFOCOMMAND_HPP
#define BROADWAY_SIMULATION_INFOCOMMAND_HPP

#include "../Command.hpp"

class InfoCommand : public Command {
	public:
		void execute() override;
};


#endif //BROADWAY_SIMULATION_INFOCOMMAND_HPP
