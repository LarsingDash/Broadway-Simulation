#include "InputModule.hpp"
#include "../FileReading/FileReaderTemplate.hpp"
#include <iostream>

void InputModule::handleScancode(SDL_Scancode key, bool& shouldQuit) {
	switch (key) {
		default:
			break;
		case SDL_SCANCODE_ESCAPE:
			shouldQuit = true;
			std::cout << "Escape key pressed!" << std::endl;
			break;
		case SDL_SCANCODE_O:
			FileReaderTemplate::readFileTemplate("..\\assets\\grid.txt", SourceType::File, FileType::Map);
//			FileReaderTemplate::readFileTemplate("https://firebasestorage.googleapis.com/v0/b/dpa-files.appspot.com/o/graph.xml?alt=media", SourceType::Web, FileType::Map);
//			FileReaderTemplate::readFileTemplate("https://firebasestorage.googleapis.com/v0/b/dpa-files.appspot.com/o/grid.txt?alt=media", SourceType::Web, FileType::Map);
			break;
	}
}
