//
// Created by larsv on 03/10/2024.
//

#ifndef BROADWAY_SIMULATION_WEBSOURCESTRATEGY_HPP
#define BROADWAY_SIMULATION_WEBSOURCESTRATEGY_HPP

#include "ISourceStrategy.hpp"

class WebSourceStrategy : public ISourceStrategy {
	public:
		std::unique_ptr<Source> fetchSource(const std::string& pathOrURL) override;
};

#endif //BROADWAY_SIMULATION_WEBSOURCESTRATEGY_HPP
