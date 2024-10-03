//
// Created by larsv on 03/10/2024.
//

#ifndef BROADWAY_SIMULATION_ARTISTSTRATEGY_HPP
#define BROADWAY_SIMULATION_ARTISTSTRATEGY_HPP

#include "../Source.hpp"

class ArtistStrategy {
		virtual void parseMap(const Source& source) = 0;
};

#endif //BROADWAY_SIMULATION_ARTISTSTRATEGY_HPP
