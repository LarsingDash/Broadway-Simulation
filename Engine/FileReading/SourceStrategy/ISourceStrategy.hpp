//
// Created by larsv on 03/10/2024.
//

#ifndef BROADWAY_SIMULATION_ISOURCESTRATEGY_HPP
#define BROADWAY_SIMULATION_ISOURCESTRATEGY_HPP

#include "../Source.hpp"
#include <memory>
#include <fstream>

class ISourceStrategy {
	public:
		virtual ~ISourceStrategy() = default;
		virtual std::unique_ptr<Source> fetchSource(const std::string& pathOrURL) = 0;
};

#endif //BROADWAY_SIMULATION_ISOURCESTRATEGY_HPP
