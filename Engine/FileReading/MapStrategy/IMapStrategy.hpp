//
// Created by larsv on 08/10/2024.
//

#ifndef BROADWAY_SIMULATION_IMAPSTRATEGY_HPP
#define BROADWAY_SIMULATION_IMAPSTRATEGY_HPP

#include "../Source.hpp"
#include <iostream>

class IMapStrategy {
	public:
		virtual ~IMapStrategy() = default;
		virtual void parseMap(const Source& source) = 0;
};

#endif //BROADWAY_SIMULATION_IMAPSTRATEGY_HPP
