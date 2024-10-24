//
// Created by larsv on 24/10/2024.
//

#include "CollisionModule.hpp"

const char* CollisionModule::CollisionTypeItems[] = {
		"Naive",
		"Quadtree",
};

CollisionModule::CollisionModule(ArtistsManager& artistsManager, PathfindingModule& pathfindingModule,
								 RenderingModule& renderingModule) : artistsManager{artistsManager},
																	 pathfindingModule{pathfindingModule},
																	 renderingModule{renderingModule} {}

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
