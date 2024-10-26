//
// Created by larsv on 24/10/2024.
//

#ifndef BROADWAY_SIMULATION_COLLISIONMODULE_HPP
#define BROADWAY_SIMULATION_COLLISIONMODULE_HPP

#include "../../Artists/ArtistsManager.hpp"
#include "PathfindingModule.hpp"
#include "../RenderingModule.hpp"
#include "Quadtree.hpp"

class CollisionModule {
	public:
		CollisionModule(ArtistsManager& artistsManager, PathfindingModule& pathfindingModule,
						RenderingModule& renderingModule);

		void update();
		void renderInfo();

		enum CollisionType {
			Naive,
			Qt,
			Count, //ALWAYS KEEP LAST
		};
		static const char* CollisionTypeItems[];
		
		void setCollisionType(CollisionType collisionType);
		void toggleCollisionInfo();
		void toggleCollideWithPath();

		std::unique_ptr<Quadtree> quadtree;
	private:
		void _naiveCollision();
		void _quadtreeCollision();
		void _quadtreeCollisionInfo();
		
		CollisionType collisionType{CollisionType::Qt};
		bool renderCollisionInfo{false};
		bool collideWithPath{false};
		

		ArtistsManager& artistsManager;
		PathfindingModule& pathfindingModule;
		RenderingModule& renderingModule;
};


#endif //BROADWAY_SIMULATION_COLLISIONMODULE_HPP
