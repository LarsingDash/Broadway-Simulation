//
// Created by larsv on 03/10/2024.
//

#ifndef BROADWAY_SIMULATION_IARTISTSTRATEGY_HPP
#define BROADWAY_SIMULATION_IARTISTSTRATEGY_HPP

#include "../Source.hpp"
#include <iostream>

class IArtistStrategy {
	public:
		virtual ~IArtistStrategy() = default;
		virtual void parseArtists(const Source& source) = 0;
};

#endif //BROADWAY_SIMULATION_IARTISTSTRATEGY_HPP
