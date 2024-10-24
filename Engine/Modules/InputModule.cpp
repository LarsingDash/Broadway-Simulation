#include "InputModule.hpp"
#include "../SimulationManager.hpp"
#include "../CommandHandling/Commands/RewindCommand.hpp"
#include "../CommandHandling/Commands/RenderArtistsCommand.hpp"
#include "../CommandHandling/Commands/FileSelectionCommand.hpp"
#include "../CommandHandling/Commands/PlayPauseCommand.hpp"
#include "../CommandHandling/Commands/FastForwardCommand.hpp"
#include "../CommandHandling/Commands/QuitCommand.hpp"
#include "../CommandHandling/Commands/InfoCommand.hpp"

InputModule::InputModule() {
	keys[Commands::PlayPause] = {SDL_SCANCODE_SPACE, "PlayPause"};
	keys[Commands::FileSelection] = {SDL_SCANCODE_O, "FileSelection"};
	keys[Commands::RenderArtists] = {SDL_SCANCODE_A, "RenderArtists"};
	keys[Commands::Rewind] = {SDL_SCANCODE_LEFT, "Rewind"};
	keys[Commands::FastForward] = {SDL_SCANCODE_RIGHT, "FastForward"};
	keys[Commands::Quit] = {SDL_SCANCODE_ESCAPE, "Quit"};
	keys[Commands::Info] = {SDL_SCANCODE_M, "Info"};

	commandBindings[Commands::PlayPause] = std::make_unique<PlayPauseCommand>();
	commandBindings[Commands::FileSelection] = std::make_unique<FileSelectionCommand>();
	commandBindings[Commands::RenderArtists] = std::make_unique<RenderArtistsCommand>();
	commandBindings[Commands::Rewind] = std::make_unique<RewindCommand>();
	commandBindings[Commands::FastForward] = std::make_unique<FastForwardCommand>();
	commandBindings[Commands::Quit] = std::make_unique<QuitCommand>();
	commandBindings[Commands::Info] = std::make_unique<InfoCommand>();
}

void InputModule::handleScancode(SDL_Scancode key) {
	//Ignore everything but the QuitCommand key when any window is focussed
	GUIModule& guiModule = *SimulationManager::getInstance().guiModule;
	if (GUIModule::isTyping) return;
	if (key != keys[Commands::Quit].first && (guiModule.getFileSelectionFocussed() || guiModule.getInfoFocussed())) return;

	//Find the command corresponding with the pressed key
	for (const auto& [command, boundKey]: keys) {
		if (boundKey.first == key) {
			//Call the command
			commandBindings[command]->execute();
			break;
		}
	}
}

void InputModule::handleMouseClick() {
	//Call TileInteraction on mouse click, unless absorbed by a window
	GUIModule& guiModule = *SimulationManager::getInstance().guiModule;
}
