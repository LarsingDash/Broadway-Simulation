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
