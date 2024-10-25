//
// Created by larsv on 24/10/2024.
//

#include "CollisionModule.hpp"
#include "WindowModule.hpp"

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
    const auto& artists = artistsManager.getArtists();
    for (const auto& artist : artists) {
        artist->isColliding = false;
    }

    // Check collisions between artists
    for (size_t i = 0; i < artists.size(); i++) {
        for (size_t j = i + 1; j < artists.size(); j++) {
            const auto& artist1 = artists[i];
            const auto& artist2 = artists[j];

            // Check if bounding boxes overlap :)
            bool collision =
                    artist1->pos.x < artist2->pos.x + Artist::size.x &&
                    artist1->pos.x + Artist::size.x > artist2->pos.x &&
                    artist1->pos.y < artist2->pos.y + Artist::size.y &&
                    artist1->pos.y + Artist::size.y > artist2->pos.y;

            if (collision) {
                std::cout << "Collision detected!" << std::endl;
                artist1->isColliding = true;
                artist2->isColliding = true;
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
