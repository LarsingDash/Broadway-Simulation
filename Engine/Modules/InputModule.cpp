#include "InputModule.hpp"

InputModule::InputModule() {
	commands[SDL_SCANCODE_SPACE] = std::make_unique<PlayPauseCommand>();
	commands[SDL_SCANCODE_RETURN] = std::make_unique<TileInteractionCommand>();
	commands[SDL_SCANCODE_O] = std::make_unique<FileSelectionCommand>();
	commands[SDL_SCANCODE_A] = std::make_unique<RenderArtistsCommand>();
	commands[SDL_SCANCODE_LEFT] = std::make_unique<RewindCommand>();
	commands[SDL_SCANCODE_RIGHT] = std::make_unique<FastForwardCommand>();
	commands[SDL_SCANCODE_ESCAPE] = std::make_unique<QuitCommand>();
}

void InputModule::handleScancode(SDL_Scancode key) {
	//Ignore everything but the QuitCommand key when FileSelection is opened
	if (key != SDL_SCANCODE_ESCAPE && SimulationManager::getInstance().guiModule->getFileSelectionFocussed()) return;

	auto it = commands.find(key);
	if (it != commands.end()) {
		it->second->execute();
	}
}

void InputModule::handleMouseClick() {
	if (!SimulationManager::getInstance().guiModule->getFileSelectionFocussed())
		commands[SDL_SCANCODE_RETURN]->execute();
}
