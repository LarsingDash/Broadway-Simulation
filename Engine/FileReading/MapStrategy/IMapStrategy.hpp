//
// Created by larsv on 08/10/2024.
//

#ifndef BROADWAY_SIMULATION_IMAPSTRATEGY_HPP
#define BROADWAY_SIMULATION_IMAPSTRATEGY_HPP

#include "../../Tiles/MuseumBuilder.hpp"
#include <iostream>

class IMapStrategy {
	public:
		virtual ~IMapStrategy() = default;
		virtual void parseMap(const std::vector<std::string>& data) = 0;
};

#endif //BROADWAY_SIMULATION_IMAPSTRATEGY_HPP
