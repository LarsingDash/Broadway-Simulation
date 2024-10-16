//
// Created by larsv on 03/10/2024.
//

#include "FileReaderTemplate.hpp"
#include "SourceStrategy/WebSourceStrategy.hpp"
#include "SourceStrategy/FileSourceStrategy.hpp"
#include "MapStrategy/XmlMapStrategy.hpp"
#include "MapStrategy/TxtMapStrategy.hpp"
#include "ArtistStrategy/CsvArtistStrategy.hpp"
#include <memory>

std::vector<std::unique_ptr<IParseStrategy>> FileReaderTemplate::strategies;

void FileReaderTemplate::assignStrategies() {
	if (!strategies.empty()) return;

	strategies.emplace_back(std::make_unique<TxtMapStrategy>());
	strategies.emplace_back(std::make_unique<XmlMapStrategy>());
	strategies.emplace_back(std::make_unique<CsvArtistStrategy>());
}

void FileReaderTemplate::readFileTemplate(const std::string& pathOrURL, SourceType sourceType) {
	FileReaderTemplate::assignStrategies();
	
	//Decide Source Strategy
	std::unique_ptr<ISourceStrategy> sourceStrategy;
	switch (sourceType) {
		default:
		case File:
			sourceStrategy = std::make_unique<FileSourceStrategy>();
			break;
		case Web:
			sourceStrategy = std::make_unique<WebSourceStrategy>();
			break;
	}

	//Get Source: if fetchSource returns false, there's been an error, so return early to avoid reading the nonexistent result
	std::vector<std::string> data;
	if (!sourceStrategy->fetchSource(pathOrURL, data)) return;

	//Find Strategy that's compatible with the data and execute it
	bool foundCompatibleStrategy = false;
	for (const auto& strategy: FileReaderTemplate::strategies) {
		if (strategy->checkCompatibility(data)) {
			strategy->parseStrategy(data);
			foundCompatibleStrategy = true;
			break;
		}
	}

	if (!foundCompatibleStrategy)
		std::cerr << "Data was not compatible with any registered Strategy" << std::endl;
}
