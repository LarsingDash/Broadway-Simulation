//
// Created by larsv on 03/10/2024.
//

#ifndef BROADWAY_SIMULATION_ISOURCESTRATEGY_HPP
#define BROADWAY_SIMULATION_ISOURCESTRATEGY_HPP

#include <vector>
#include <memory>
#include <fstream>

class ISourceStrategy {
	public:
		virtual ~ISourceStrategy() = default;
		virtual void fetchSource(const std::string& pathOrURL, std::vector<std::string>& data) = 0;
};

#endif //BROADWAY_SIMULATION_ISOURCESTRATEGY_HPP
