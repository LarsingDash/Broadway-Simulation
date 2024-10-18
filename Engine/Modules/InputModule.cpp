#include "InputModule.hpp"
#include "../SimulationManager.hpp"
#include "../CommandHandling/Commands/RewindCommand.hpp"
#include "../CommandHandling/Commands/RenderArtistsCommand.hpp"
#include "../CommandHandling/Commands/FileSelectionCommand.hpp"
#include "../CommandHandling/Commands/PlayPauseCommand.hpp"
#include "../CommandHandling/Commands/TileInteractionCommand.hpp"
#include "../CommandHandling/Commands/FastForwardCommand.hpp"
#include "../CommandHandling/Commands/QuitCommand.hpp"
#include "../CommandHandling/Commands/InfoCommand.hpp"

InputModule::InputModule() {
	commands[SDL_SCANCODE_SPACE] = std::make_unique<PlayPauseCommand>();
	commands[SDL_SCANCODE_RETURN] = std::make_unique<TileInteractionCommand>();
	commands[SDL_SCANCODE_O] = std::make_unique<FileSelectionCommand>();
	commands[SDL_SCANCODE_A] = std::make_unique<RenderArtistsCommand>();
	commands[SDL_SCANCODE_LEFT] = std::make_unique<RewindCommand>();
	commands[SDL_SCANCODE_RIGHT] = std::make_unique<FastForwardCommand>();
	commands[SDL_SCANCODE_ESCAPE] = std::make_unique<QuitCommand>();
	commands[SDL_SCANCODE_M] = std::make_unique<InfoCommand>();
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
	GUIModule& guiModule = *SimulationManager::getInstance().guiModule;
	if (!(guiModule.getFileSelectionFocussed() || guiModule.getInfoFocussed()))
		commands[SDL_SCANCODE_RETURN]->execute();
}
