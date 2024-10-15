//
// Created by larsv on 08/10/2024.
//

#ifndef BROADWAY_SIMULATION_IPARSESTRATEGY_HPP
#define BROADWAY_SIMULATION_IPARSESTRATEGY_HPP

#include "../Tiles/MuseumBuilder.hpp"
#include <iostream>

class IParseStrategy {
	public:
		virtual ~IParseStrategy() = default;
		virtual bool checkCompatibility(const std::vector<std::string>& data) = 0;
		virtual void parseStrategy(const std::vector<std::string>& data) = 0;
};

#endif //BROADWAY_SIMULATION_IPARSESTRATEGY_HPP
