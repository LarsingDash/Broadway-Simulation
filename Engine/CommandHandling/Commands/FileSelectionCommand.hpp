//
// Created by 11896 on 11/10/2024.
//

#ifndef BROADWAY_SIMULATION_FILESELECTIONCOMMAND_HPP
#define BROADWAY_SIMULATION_FILESELECTIONCOMMAND_HPP

#include "../Command.hpp"
#include "../../FileReading/FileReaderTemplate.hpp"
#include <iostream>

class FileSelectionCommand : public Command {
	public:
		void execute() override;
};

#endif //BROADWAY_SIMULATION_FILESELECTIONCOMMAND_HPP