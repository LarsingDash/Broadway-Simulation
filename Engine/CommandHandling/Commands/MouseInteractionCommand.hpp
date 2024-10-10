//
// Created by 11896 on 11/10/2024.
//

#ifndef BROADWAY_SIMULATION_MOUSEINTERACTIONCOMMAND_HPP
#define BROADWAY_SIMULATION_MOUSEINTERACTIONCOMMAND_HPP

#include <iostream>
#include "../Command.hpp"
#include "../../SimulationManager.hpp"
class MouseInteractionCommand :public Command{
    SimulationManager* simManager;
    void execute() override{
        std::cout << "MouseInteractionCommand exectued" << std::endl;
        simManager->interactTileAtMouse();
    }
};


#endif //BROADWAY_SIMULATION_MOUSEINTERACTIONCOMMAND_HPP
