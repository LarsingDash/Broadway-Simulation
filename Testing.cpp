//
// Created by larsv on 23/10/2024.
//

#include "Testing.hpp"
#include "Engine/FileReading/FileReaderTemplate.hpp"
#include <functional>
#include <sstream>

std::string Testing::error;

int Testing::RunTests() {
	//Get simulationManager
	SimulationManager& simulationManager = SimulationManager::getInstance();

	//Assign tests
	std::vector<std::pair<std::string, std::function<void(SimulationManager& simulationManager)>>> tests{
			{"_fileReading",     Testing::_fileReading},
			{"_tileInteraction", Testing::_tileInteraction},
			{"_artistUpdate",    Testing::_artistUpdate},
	};

	//Run all tests, if one has changed Testing::error: print it and return 1
	for (const auto& test: tests) {
		test.second(simulationManager);
		if (!Testing::error.empty()) {
			std::cerr << test.first << ": " << Testing::error << std::endl;
			return 1;
		}
	}

	//Return 0 indicating no tests failed
	std::cout << "All tests succeeded!" << std::endl;
	return 0;
}

void Testing::_fileReading(SimulationManager& simulationManager) {
	Museum& museum = *simulationManager.museum;

	//Read test.txt file, should set a 3x3 museum
	FileReaderTemplate::readFileTemplate("..\\assets\\test.txt", SourceType::File);

	//Test museum dimensions
	if (museum.getRows() != 3) Testing::error = "Rows wasn't correctly set";
	if (museum.getCols() != 3) Testing::error = "Cols wasn't correctly set";

	//Test tiles
	char grid[3][3]{
			{'W', 'R', 'G'},
			{'W', 'G', 'R'},
			{'G', 'R', 'G'},
	};

	//Check all tiles if they match the expectation
	for (int y = 0; y < museum.getRows(); y++) {
		for (int x = 0; x < museum.getCols(); x++) {
			const char letter = museum.getTile(y, x).currentState->letter;
			const char expected = grid[x][y];

			if (letter != expected) {
				std::stringstream stream;
				stream << "(" << x << " - " << y << ") was set incorrectly: expected " << expected << " but got "
					   << letter;
				Testing::error = stream.str();
				return;
			}
		}
	}
}

void Testing::_tileInteraction(SimulationManager& simulationManager) {
	Tile& tile = simulationManager.museum->getTile(1, 1);

	//Trigger (1, 1) twice, should still be grey
	if (tile.currentState->letter != 'G') {
		Testing::error = "Wrong starting state";
		return;
	}

	tile.currentState->handleInteraction(tile, nullptr);
	tile.currentState->handleInteraction(tile, nullptr);

	if (tile.currentState->letter != 'G') {
		Testing::error = "Tile (1, 1) changed too early";
		return;
	}

	//Trigger (1, 1) one more time to make it red
	tile.currentState->handleInteraction(tile, nullptr);
	if (tile.currentState->letter != 'R') Testing::error = "Tile (1, 1) didn't change to Red";
}

void Testing::_artistUpdate(SimulationManager& simulationManager) {
	ArtistsManager& artistsManager = *simulationManager.artistsManager;
	Museum& museum = *simulationManager.museum;

	//Create an artist
	artistsManager.addArtist({1, 1}, {0, 1.f});

	//Move artist to the tile below it
	artistsManager.update(museum, 1.f);

	//Artist moving onto the red tile should've deleted it and made the tile Blue
	if (museum.getTile(1, 2).currentState->letter != 'B')
		Testing::error = "Red wasn't set to blue after artist moved onto it";
}
