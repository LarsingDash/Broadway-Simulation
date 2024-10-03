//
// Created by larsv on 03/10/2024.
//

#include <memory>
#include "FileReaderTemplate.hpp"
#include "SourceStrategy/WebSourceStrategy.hpp"
#include "SourceStrategy/FileSourceStrategy.hpp"

void FileReaderTemplate::readFileTemplate(const std::string& pathOrURL, SourceType sourceType, FileType fileType) {
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

	std::unique_ptr<Source> source = sourceStrategy->fetchSource(pathOrURL);
	std::cout << "------------------------------" << std::endl;
	std::cout << "Input: " << pathOrURL << "\tas " << source->extension << "\n" << std::endl;
	std::cout << "--------------" << std::endl;
	for (const auto& line: source->data) {
		std::cout << line << std::endl;
	}
}
