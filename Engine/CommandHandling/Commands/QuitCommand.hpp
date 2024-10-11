//
// Created by 11896 on 11/10/2024.
//
#ifndef BROADWAY_SIMULATION_QUITCOMMAND_HPP
#define BROADWAY_SIMULATION_QUITCOMMAND_HPP

#include "../Command.hpp"
#include "../../SimulationManager.hpp"

class QuitCommand : public Command {
public:
    void execute() override;
};

#endif //BROADWAY_SIMULATION_QUITCOMMAND_HPP

