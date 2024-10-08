//
// Created by larsv on 03/10/2024.
//

#include <memory>
#include "FileReaderTemplate.hpp"
#include "SourceStrategy/WebSourceStrategy.hpp"
#include "SourceStrategy/FileSourceStrategy.hpp"
#include "ArtistStrategy/IArtistStrategy.hpp"
#include "MapStrategy/IMapStrategy.hpp"
#include "MapStrategy/XmlMapStrategy.hpp"
#include "MapStrategy/TxtMapStrategy.hpp"
#include "ArtistStrategy/CsvArtistStrategy.hpp"

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
	
	//Execute Map / Artist Strategy to parse Source
	if (fileType == FileType::Map) {
		//Decide Map Strategy
		std::unique_ptr<IMapStrategy> mapStrategy = nullptr;
		if (source->extension == "xml") mapStrategy = std::make_unique<XmlMapStrategy>();
		else if (source->extension == "txt") mapStrategy = std::make_unique<TxtMapStrategy>();
		
		//Parse Source to Map
		if (mapStrategy) mapStrategy->parseMap(*source);
		else std::cout << "No Map Strategy Found" << std::endl;;
	} else {
		//Decide Artist Strategy
		std::unique_ptr<IArtistStrategy> artistStrategy;
		if (source->extension == "csv") artistStrategy = std::make_unique<CsvArtistStrategy>();
		
		//Parse Source to Artist
		if (artistStrategy) artistStrategy->parseArtists(*source);
		else std::cout << "No Artist Strategy Found" << std::endl;;
	}
}
