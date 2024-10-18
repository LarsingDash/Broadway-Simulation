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
	keys[Commands::PlayPause] = SDL_SCANCODE_SPACE;
	keys[Commands::TileInteraction] = SDL_SCANCODE_RETURN;
	keys[Commands::FileSelection] = SDL_SCANCODE_O;
	keys[Commands::RenderArtists] = SDL_SCANCODE_A;
	keys[Commands::Rewind] = SDL_SCANCODE_LEFT;
	keys[Commands::FastForward] = SDL_SCANCODE_RIGHT;
	keys[Commands::Quit] = SDL_SCANCODE_ESCAPE;
	keys[Commands::Info] = SDL_SCANCODE_M;

	commandBindings[Commands::PlayPause] = std::make_unique<PlayPauseCommand>();
	commandBindings[Commands::TileInteraction] = std::make_unique<TileInteractionCommand>();
	commandBindings[Commands::FileSelection] = std::make_unique<FileSelectionCommand>();
	commandBindings[Commands::RenderArtists] = std::make_unique<RenderArtistsCommand>();
	commandBindings[Commands::Rewind] = std::make_unique<RewindCommand>();
	commandBindings[Commands::FastForward] = std::make_unique<FastForwardCommand>();
	commandBindings[Commands::Quit] = std::make_unique<QuitCommand>();
	commandBindings[Commands::Info] = std::make_unique<InfoCommand>();
}

void InputModule::handleScancode(SDL_Scancode key) {
	//Ignore everything but the QuitCommand key when FileSelection is focussed
	if (key != keys[Commands::Quit] && SimulationManager::getInstance().guiModule->getFileSelectionFocussed()) return;

	//Find the command corresponding with the pressed key
	for (const auto& [command, boundKey]: keys) {
		if (boundKey == key) {
			//Call the command
			commandBindings[command]->execute();
			break;
		}
	}
}

void InputModule::handleMouseClick() {
	//Call TileInteraction on mouse click, unless absorbed by a window
	GUIModule& guiModule = *SimulationManager::getInstance().guiModule;
	if (!(guiModule.getFileSelectionFocussed() || guiModule.getInfoFocussed()))
		commandBindings[Commands::TileInteraction]->execute();
}
