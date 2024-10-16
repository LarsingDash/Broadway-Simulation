//
// Created by 11896 on 11/10/2024.
//

#ifndef BROADWAY_SIMULATION_RENDERARTISTSCOMMAND_HPP
#define BROADWAY_SIMULATION_RENDERARTISTSCOMMAND_HPP

#include <iostream>
#include "../Command.hpp"
class RenderArtistsCommand :public Command{
    void execute() override{
        std::cout << "RenderArtistsCommand exectued" << std::endl;
    }
};


#endif //BROADWAY_SIMULATION_RENDERARTISTSCOMMAND_HPP
