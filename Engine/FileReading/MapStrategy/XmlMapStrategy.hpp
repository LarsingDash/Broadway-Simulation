﻿//
// Created by larsv on 08/10/2024.
//

#ifndef BROADWAY_SIMULATION_XMLMAPSTRATEGY_HPP
#define BROADWAY_SIMULATION_XMLMAPSTRATEGY_HPP


#include "IMapStrategy.hpp"

class XmlMapStrategy : public IMapStrategy {
		void parseMap(const std::vector<std::string>& data) override;
};

#endif //BROADWAY_SIMULATION_XMLMAPSTRATEGY_HPP
