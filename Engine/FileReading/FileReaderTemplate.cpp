//
// Created by larsv on 03/10/2024.
//

#include "FileReaderTemplate.hpp"
#include "SourceStrategy/WebSourceStrategy.hpp"
#include "SourceStrategy/FileSourceStrategy.hpp"
#include "MapStrategy/IMapStrategy.hpp"
#include "MapStrategy/XmlMapStrategy.hpp"
#include "MapStrategy/TxtMapStrategy.hpp"
#include "ArtistStrategy/IArtistStrategy.hpp"
#include "ArtistStrategy/CsvArtistStrategy.hpp"
#include <memory>

void FileReaderTemplate::readFileTemplate(const std::string& pathOrURL, SourceType sourceType, FileType fileType) {
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
	
	//Get Source
	std::unique_ptr<Source> source = sourceStrategy->fetchSource(pathOrURL);
	
	//TODO checker for parsers if they can parse, not dependent on extension
	
	//Execute Map / Artist Strategy to parse Source
	//Use rfind() as a sort of extension.startsWith()
	if (fileType == FileType::Map) {
		//Decide Map Strategy
		std::unique_ptr<IMapStrategy> mapStrategy = nullptr;
		if (source->extension.rfind("xml") == 0) mapStrategy = std::make_unique<XmlMapStrategy>();
		else if (source->extension.rfind("txt") == 0) mapStrategy = std::make_unique<TxtMapStrategy>();
		
		//Parse Source to Map
		if (mapStrategy) mapStrategy->parseMap(source->data);
		else std::cout << "No Map Strategy found for extension: " << source->extension << std::endl;;
	} else {
		//Decide Artist Strategy
		std::unique_ptr<IArtistStrategy> artistStrategy;
		if (source->extension.rfind("csv") == 0) artistStrategy = std::make_unique<CsvArtistStrategy>();
		
		//Parse Source to Artist
		if (artistStrategy) artistStrategy->parseArtists(*source);
		else std::cout << "No Artist Strategy Found" << std::endl;;
	}
}
