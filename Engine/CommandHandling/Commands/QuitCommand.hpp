//
// Created by 11896 on 11/10/2024.
//
#ifndef BROADWAY_SIMULATION_QUITCOMMAND_HPP
#define BROADWAY_SIMULATION_QUITCOMMAND_HPP
#include <iostream>
#include "../Command.hpp"
class QuitCommand :public Command{
private:
    bool& shouldQuit;

public:
    QuitCommand(bool& quitFlag) : shouldQuit(quitFlag) {}


    void execute() override {
        std::cout << "QuitCommand executed, setting shouldQuit to true." << std::endl;
        shouldQuit = true;
    }
};


#endif //BROADWAY_SIMULATION_QUITCOMMAND_HPP
