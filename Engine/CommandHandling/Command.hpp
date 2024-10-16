//
// Created by 11896 on 11/10/2024.
//

#ifndef BROADWAY_SIMULATION_COMMAND_HPP
#define BROADWAY_SIMULATION_COMMAND_HPP

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};
#endif //BROADWAY_SIMULATION_COMMAND_HPP
