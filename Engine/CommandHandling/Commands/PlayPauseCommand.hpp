//
// Created by 11896 on 11/10/2024.
//

#ifndef BROADWAY_SIMULATION_PLAYPAUSECOMMAND_HPP
#define BROADWAY_SIMULATION_PLAYPAUSECOMMAND_HPP

#include <iostream>
#include "../Command.hpp"
class PlayPauseCommand :public Command{
    void execute() override{
        std::cout << "PlayPauseCommand exectued" << std::endl;
    }
};


#endif //BROADWAY_SIMULATION_PLAYPAUSECOMMAND_HPP
