//
// Created by larsv on 08/10/2024.
//

#ifndef BROADWAY_SIMULATION_TXTMAPSTRATEGY_HPP
#define BROADWAY_SIMULATION_TXTMAPSTRATEGY_HPP


#include "IMapStrategy.hpp"

class TxtMapStrategy : public IMapStrategy {
		void parseMap(const Source& source) override;
};


#endif //BROADWAY_SIMULATION_TXTMAPSTRATEGY_HPP
