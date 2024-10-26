//
// Created by larsv on 24/10/2024.
//

#include "CollisionModule.hpp"
#include "../WindowModule.hpp"

const char* CollisionModule::CollisionTypeItems[] = {
		"Naive",
		"Quadtree",
};

CollisionModule::CollisionModule(ArtistsManager& artistsManager, PathfindingModule& pathfindingModule,
								 RenderingModule& renderingModule) : artistsManager{artistsManager},
																	 pathfindingModule{pathfindingModule},
																	 renderingModule{renderingModule} {}

void CollisionModule::renderInfo() {
	if (!renderCollisionInfo) return;

	switch (collisionType) {
		default:
		case Naive:
			break;
		case Quadtree:
			_quadtreeCollisionInfo();
			break;
	}
}

void CollisionModule::update() {
	switch (collisionType) {
		default:
		case Naive:
			_naiveCollision();
			break;
		case Quadtree:
			_quadtreeCollision();
			break;
	}
}

void CollisionModule::setCollisionType(CollisionModule::CollisionType type) { collisionType = type; }
void CollisionModule::toggleCollisionInfo() { renderCollisionInfo = !renderCollisionInfo; }
void CollisionModule::toggleCollideWithPath() { collideWithPath = !collideWithPath; }

void CollisionModule::_naiveCollision() {
	// Get artists and reset colliding flags
    const auto& artists = artistsManager.getArtists();
    for (const auto& artist : artists) {
        artist->isColliding = false;
    }

    // Check collisions between artists
    for (size_t i = 0; i < artists.size(); i++) {
		const auto& currentArtist = artists[i];
        for (size_t j = i + 1; j < artists.size(); j++) {
            const auto& otherArtist = artists[j];

            // Check if bounding boxes overlap :)
            bool collision =
					currentArtist->pos.x < otherArtist->pos.x + Artist::size.x &&	//left of cur before right of other
					currentArtist->pos.x + Artist::size.x > otherArtist->pos.x &&	//right of cur after left of other
					currentArtist->pos.y < otherArtist->pos.y + Artist::size.y &&	//top cur before bottom of other
					currentArtist->pos.y + Artist::size.y > otherArtist->pos.y;		//bottom of cur after top of other

            if (collision) {
				currentArtist->isColliding = true;
				otherArtist->isColliding = true;
            }
        }
    }
    if (collideWithPath && pathfindingModule.getRenderPath()) {
        const auto& path = pathfindingModule.getPath();
        const auto& tileSize = RenderingModule::tileSize;

        for (const auto& artist : artists) {
            for (const auto* tile : path) {
                glm::vec2 tilePos = glm::vec2(tile->getPos()) * tileSize;

                bool collision =
                        artist->pos.x < tilePos.x + tileSize.x &&
                        artist->pos.x + Artist::size.x > tilePos.x &&
                        artist->pos.y < tilePos.y + tileSize.y &&
                        artist->pos.y + Artist::size.y > tilePos.y;

                if (collision) {
                    artist->isColliding = true;
                    break;
                }
            }
        }
    }

}

void CollisionModule::_quadtreeCollision() {

}

void CollisionModule::_quadtreeCollisionInfo() {
	int width = WindowModule::width;
	int height = WindowModule::height;
	renderingModule.drawRectangle({0, 0, width, height}, true);
	renderingModule.drawRectangle({0, 0, width / 2, height / 2}, true);
	renderingModule.drawRectangle({width / 2, 0, width / 2, height / 2}, true);
}
