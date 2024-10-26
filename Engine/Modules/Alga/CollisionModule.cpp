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
		case Qt:
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
		case Qt:
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
	for (const auto& artist: artists) {
		artist->isColliding = false;
	}

	// Check collisions between artists
	for (size_t i = 0; i < artists.size(); i++) {
		const auto& currentArtist = artists[i];
		for (size_t j = i + 1; j < artists.size(); j++) {
			const auto& otherArtist = artists[j];

			// Check if bounding boxes overlap :)
			bool collision =
					currentArtist->pos.x < otherArtist->pos.x + Artist::size.x &&    //left of cur before right of other
					currentArtist->pos.x + Artist::size.x > otherArtist->pos.x &&    //right of cur after left of other
					currentArtist->pos.y < otherArtist->pos.y + Artist::size.y &&    //top cur before bottom of other
					currentArtist->pos.y + Artist::size.y >
					otherArtist->pos.y;        //bottom of cur after top of other

			if (collision) {
				currentArtist->isColliding = true;
				otherArtist->isColliding = true;
			}
		}
	}
	if (collideWithPath && pathfindingModule.getRenderPath()) {
		const auto& path = pathfindingModule.getPath();
		const auto& tileSize = RenderingModule::tileSize;

		for (const auto& artist: artists) {
			for (const auto* tile: path) {
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
	const auto& tileSize = RenderingModule::tileSize;

	//Get list of artists and path
	auto& artists = artistsManager.getArtists();
	auto& path = pathfindingModule.path;

	//Make a list of all colliders
	std::vector<std::unique_ptr<SDL_FRect>> colliders{};
	for (const auto& artist: artists)
		colliders.emplace_back(std::make_unique<SDL_FRect>(
				SDL_FRect{artist->pos.x, artist->pos.y, Artist::size.x, Artist::size.y}
		));
	for (const auto& tile: path) {
		glm::vec2 tilePos = glm::vec2(tile->getPos()) * tileSize;
		colliders.emplace_back(std::make_unique<SDL_FRect>(
				SDL_FRect{tilePos.x, tilePos.y, tileSize.x, tileSize.y}
		));
	}

	//Initialize root
	quadtree = std::make_unique<Quadtree>(0, 0, 0, WindowModule::width, WindowModule::height);

	//Loop through all colliders and add to the quadtree from the root
	for (const auto& collider: colliders)
		quadtree->addCollider(collider.get());
}

void CollisionModule::_quadtreeCollisionInfo() {
	if (quadtree) quadtree->render(renderingModule);
}
