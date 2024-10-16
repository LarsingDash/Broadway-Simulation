//
// Created by 11896 on 11/10/2024.
//

#ifndef BROADWAY_SIMULATION_REWINDCOMMAND_HPP
#define BROADWAY_SIMULATION_REWINDCOMMAND_HPP

#include <iostream>
#include "../Command.hpp"
class RewindCommand :public Command{
    void execute() override{
        std::cout << "RewindCommand exectued" << std::endl;
    }
};


#endif //BROADWAY_SIMULATION_REWINDCOMMAND_HPP
