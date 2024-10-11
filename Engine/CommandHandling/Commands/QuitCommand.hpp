//
// Created by 11896 on 11/10/2024.
//
#ifndef BROADWAY_SIMULATION_QUITCOMMAND_HPP
#define BROADWAY_SIMULATION_QUITCOMMAND_HPP
#include <iostream>
#include "../Command.hpp"
class QuitCommand :public Command{
    void execute() override{
        std::cout << "QuitCommand exectued" << std::endl;
    }
};


#endif //BROADWAY_SIMULATION_QUITCOMMAND_HPP
