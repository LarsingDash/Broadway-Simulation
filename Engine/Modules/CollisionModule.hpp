//
// Created by larsv on 24/10/2024.
//

#ifndef BROADWAY_SIMULATION_COLLISIONMODULE_HPP
#define BROADWAY_SIMULATION_COLLISIONMODULE_HPP

#include "../Artists/ArtistsManager.hpp"
#include "PathfindingModule.hpp"
#include "RenderingModule.hpp"

class CollisionModule {
	public:
		CollisionModule(ArtistsManager& artistsManager, PathfindingModule& pathfindingModule,
						RenderingModule& renderingModule);

		void update();

		enum CollisionType {
			Naive,
			Quadtree,
			Count, //ALWAYS KEEP LAST
		};
		static const char* CollisionTypeItems[];
		
		void setCollisionType(CollisionType collisionType);
		void toggleCollisionInfo();
		void toggleCollideWithPath();

	private:
		void _naiveCollision();
		void _quadtreeCollision();
		
		CollisionType collisionType{CollisionType::Quadtree};
		bool renderCollisionInfo{false};
		bool collideWithPath{false};

		ArtistsManager& artistsManager;
		PathfindingModule& pathfindingModule;
		RenderingModule& renderingModule;
};


#endif //BROADWAY_SIMULATION_COLLISIONMODULE_HPP
