//
// Created by 11896 on 11/10/2024.
//

#ifndef BROADWAY_SIMULATION_MOUSEINTERACTIONCOMMAND_HPP
#define BROADWAY_SIMULATION_MOUSEINTERACTIONCOMMAND_HPP

#include <iostream>
#include "../Command.hpp"
class MouseInteractionCommand :public Command{
    void execute() override{
        std::cout << "MouseInteractionCommand exectued" << std::endl;
    }
};


#endif //BROADWAY_SIMULATION_MOUSEINTERACTIONCOMMAND_HPP
