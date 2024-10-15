#include "InputModule.hpp"
#include "../FileReading/FileReaderTemplate.hpp"
#include <iostream>

void InputModule::handleScancode(SDL_Scancode key, bool& shouldQuit) {
	//TODO build a map<SCANCODE, Command> from imgui, so that it is changeable on runtime (including modifier keys)
	switch (key) {
		default:
			break;
		case SDL_SCANCODE_ESCAPE:
			shouldQuit = true;
			std::cout << "Escape key pressed!" << std::endl;
			break;
		case SDL_SCANCODE_O:
			FileReaderTemplate::assignStrategies();
			
//			FileReaderTemplate::readFileTemplate("..\\assets\\grid.txt", SourceType::File, FileType::Map);
//			FileReaderTemplate::readFileTemplate("https://firebasestorage.googleapis.com/v0/b/dpa-files.appspot.com/o/grid.txt?alt=media", SourceType::Web, FileType::Map);

//			FileReaderTemplate::readFileTemplate("..\\assets\\graph.xml", SourceType::File, FileType::Map);
//			FileReaderTemplate::readFileTemplate("https://firebasestorage.googleapis.com/v0/b/dpa-files.appspot.com/o/graph.xml?alt=media", SourceType::Web, FileType::Map);

			FileReaderTemplate::readFileTemplate("..\\assets\\artists.csv", SourceType::File, FileType::Artist);
			break;
	}
}
