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

	protected:
		static void removeBOM(std::ifstream& file) {
			//Read first 3 characters of file
			char bom[3] = {0};
			file.read(bom, 3);

			//Check for BOM
			if (!(bom[0] == '\xEF' && bom[1] == '\xBB' && bom[2] == '\xBF')) {
				//If not: got back to the start, if so: BOM is now skipped
				file.seekg(0);
			}
		}
};

#endif //BROADWAY_SIMULATION_ISOURCESTRATEGY_HPP
