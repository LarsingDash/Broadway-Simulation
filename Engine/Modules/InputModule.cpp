#include "InputModule.hpp"
#include "../SimulationManager.hpp"
#include "../CommandHandling/Commands/CollideWithPathCommand.hpp"
#include "../CommandHandling/Commands/FileSelectionCommand.hpp"
#include "../CommandHandling/Commands/InfoCommand.hpp"
#include "../CommandHandling/Commands/PlayPauseCommand.hpp"
#include "../CommandHandling/Commands/QuitCommand.hpp"
#include "../CommandHandling/Commands/RenderArtistsCommand.hpp"
#include "../CommandHandling/Commands/RenderCollisionInfoCommand.hpp"
#include "../CommandHandling/Commands/RenderPathCommand.hpp"
#include "../CommandHandling/Commands/RenderVisitedCommand.hpp"

InputModule::InputModule() {
	keys[Commands::PlayPause] = {SDL_SCANCODE_SPACE, "PlayPause"};
	keys[Commands::FileSelection] = {SDL_SCANCODE_O, "FileSelection"};
	keys[Commands::RenderCollisionInfo] = {SDL_SCANCODE_Q, "RenderCollisionInfo"};
	keys[Commands::RenderArtists] = {SDL_SCANCODE_A, "RenderArtists"};
	keys[Commands::CollideWithPath] = {SDL_SCANCODE_W, "CollideWithPath"};
	keys[Commands::RenderPath] = {SDL_SCANCODE_P, "RenderPath"};
	keys[Commands::RenderVisited] = {SDL_SCANCODE_V, "RenderVisited"};
	keys[Commands::Quit] = {SDL_SCANCODE_ESCAPE, "Quit"};
	keys[Commands::Info] = {SDL_SCANCODE_M, "Info"};
	
	commandBindings[Commands::PlayPause] = std::make_unique<PlayPauseCommand>();
	commandBindings[Commands::FileSelection] = std::make_unique<FileSelectionCommand>();
	commandBindings[Commands::RenderCollisionInfo] = std::make_unique<RenderCollisionInfoCommand>();
	commandBindings[Commands::RenderArtists] = std::make_unique<RenderArtistsCommand>();
	commandBindings[Commands::CollideWithPath] = std::make_unique<CollideWithPathCommand>();
	commandBindings[Commands::RenderPath] = std::make_unique<RenderPathCommand>();
	commandBindings[Commands::RenderVisited] = std::make_unique<RenderVisitedCommand>();
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

void InputModule::handleMouseClick(bool isLeft) {
	//Early return if one of the windows are focussed
	GUIModule& guiModule = *SimulationManager::getInstance().guiModule;
	if (guiModule.getFileSelectionFocussed() || guiModule.getInfoFocussed()) return;
	
	//Change start or end on mouseclick
	PathfindingModule& pathfindingModule = *SimulationManager::getInstance().pathfindingModule;
	Museum& museum = *SimulationManager::getInstance().museum;

	//Get x and y from cursor
	int x, y;
	SDL_GetMouseState(&x, &y);

	//Cast that to tile on museum
	glm::vec2 tileSize = RenderingModule::tileSize;
	int tileX = static_cast<int>(static_cast<float>(x) / tileSize.x);
	int tileY = static_cast<int>(static_cast<float>(y) / tileSize.y);

	//If within bounds: set start or end
	if (tileX >= 0 && tileX < museum.getCols() && tileY >= 0 && tileY < museum.getRows()) {
		Tile& clickedTile = museum.getTile(tileX, tileY);
		//Not allowed to use white as path
		if (clickedTile.currentState->letter == 'W') return;
		clickedTile.logTileData();

		if (isLeft) pathfindingModule.setStart(&clickedTile);
		else pathfindingModule.setTarget(&clickedTile);
	}
}
