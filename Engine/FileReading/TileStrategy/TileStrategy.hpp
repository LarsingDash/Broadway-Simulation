//
// Created by larsv on 03/10/2024.
//

#ifndef BROADWAY_SIMULATION_TILESTRATEGY_HPP
#define BROADWAY_SIMULATION_TILESTRATEGY_HPP

#include "../Source.hpp"

class TileStrategy {
		virtual void parseTiles(const Source& source) = 0;
};

#endif //BROADWAY_SIMULATION_TILESTRATEGY_HPP
