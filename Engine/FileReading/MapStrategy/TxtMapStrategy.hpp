//
// Created by larsv on 08/10/2024.
//

#ifndef BROADWAY_SIMULATION_TXTMAPSTRATEGY_HPP
#define BROADWAY_SIMULATION_TXTMAPSTRATEGY_HPP


#include "IMapStrategy.hpp"

class TxtMapStrategy : public IMapStrategy {
	public:
		void parseMap(const std::vector<std::string>& data) override;
	private:
		static void _readGridSize(const std::string& line, int& rows, int& cols);
		static void _readColor(MuseumBuilder& builder, const std::string& line);
		static void _readTile(MuseumBuilder& builder, const std::string& line, int currentRowI, int cols);
};


#endif //BROADWAY_SIMULATION_TXTMAPSTRATEGY_HPP
