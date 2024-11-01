//
// Created by 11896 on 11/10/2024.
//

#include "TileInteractionCommand.hpp"
#include "../../Tiles/Museum.hpp"
#include "../../Modules/RenderingModule.hpp"
#include "../../SimulationManager.hpp"
#include <SDL_mouse.h>
#include <vec2.hpp>

void TileInteractionCommand::execute() {
	Museum& museum = *SimulationManager::getInstance().museum;
	
	int x, y;
	SDL_GetMouseState(&x, &y);

	glm::vec2 tileSize = RenderingModule::tileSize;

	int tileX = static_cast<int>(static_cast<float>(x) / tileSize.x);
	int tileY = static_cast<int>(static_cast<float>(y) / tileSize.y);

	if (tileX >= 0 && tileX < museum.getCols() && tileY >= 0 && tileY < museum.getRows()) {
		Tile& clickedTile = museum.getTile(tileX, tileY);
		clickedTile.logTileData();
		clickedTile.currentState->handleInteraction(clickedTile, nullptr);
	}
}