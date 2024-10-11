//
// Created by larsv on 08/10/2024.
//

#ifndef BROADWAY_SIMULATION_XMLMAPSTRATEGY_HPP
#define BROADWAY_SIMULATION_XMLMAPSTRATEGY_HPP


#include "IMapStrategy.hpp"
#include <functional>

class XmlMapStrategy : public IMapStrategy {
	public:
		XmlMapStrategy();
		void parseMap(const std::vector<std::string>& data) override;
	private:
		const std::unordered_map<std::string, std::function<void(const std::string& line, bool isEnd)>> tagActions;
		std::unique_ptr<MuseumBuilder> builder;
		glm::ivec2 currentTile = glm::ivec2 ();
		
		void _readTag(const std::string& line);
		static void _readGridSize(const std::string& line, int& rows, int& cols);
		
		static constexpr size_t _readingOffset = sizeof("=\"") - 1;
		static char _readChar(const std::string& line, const std::string& target);
		static int _readInt(const std::string& line, const std::string& target);
		
};

#endif //BROADWAY_SIMULATION_XMLMAPSTRATEGY_HPP
