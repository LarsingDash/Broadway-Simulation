//
// Created by larsv on 08/10/2024.
//

#ifndef BROADWAY_SIMULATION_CSVARTISTSTRATEGY_HPP
#define BROADWAY_SIMULATION_CSVARTISTSTRATEGY_HPP

#include "../IParseStrategy.hpp"

class CsvArtistStrategy : public IParseStrategy {
	public:
		bool checkCompatibility(const std::vector<std::string>& data) override;
		void parseStrategy(const std::vector<std::string>& data) override;
};


#endif //BROADWAY_SIMULATION_CSVARTISTSTRATEGY_HPP
