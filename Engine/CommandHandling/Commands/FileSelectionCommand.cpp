//
// Created by 11896 on 11/10/2024.
//

#include "FileSelectionCommand.hpp"

void FileSelectionCommand::execute() {
	std::cout << "FileSelectionCommand executed" << std::endl;

	FileReaderTemplate::assignStrategies();

	FileReaderTemplate::readFileTemplate("..\\assets\\grid.txt", SourceType::File);
//		FileReaderTemplate::readFileTemplate("https://firebasestorage.googleapis.com/v0/b/dpa-files.appspot.com/o/grid.txt?alt=media", SourceType::Web);

//        FileReaderTemplate::readFileTemplate("..\\assets\\graph.xml", SourceType::File);
//		FileReaderTemplate::readFileTemplate("https://firebasestorage.googleapis.com/v0/b/dpa-files.appspot.com/o/graph.xml?alt=media", SourceType::Web);

	FileReaderTemplate::readFileTemplate("..\\assets\\artists.csv", SourceType::File);
}