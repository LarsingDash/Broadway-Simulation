//
// Created by larsv on 08/10/2024.
//

#ifndef BROADWAY_SIMULATION_CSVARTISTSTRATEGY_HPP
#define BROADWAY_SIMULATION_CSVARTISTSTRATEGY_HPP


#include "IArtistStrategy.hpp"

class CsvArtistStrategy : public IArtistStrategy {
	public:
		void parseArtists(const Source& source) override;
};


#endif //BROADWAY_SIMULATION_CSVARTISTSTRATEGY_HPP
