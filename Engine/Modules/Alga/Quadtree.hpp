//
// Created by larsv on 26/10/2024.
//

#ifndef BROADWAY_SIMULATION_QUADTREE_HPP
#define BROADWAY_SIMULATION_QUADTREE_HPP

#include "../RenderingModule.hpp"
#include <SDL_rect.h>
#include <vector>

class Quadtree {
	public:
		Quadtree(int depth, bool collideWithPath, int x, int y, int width, int height);
		void render(RenderingModule& renderingModule) const;
		void addCollider(SDL_FRect* collider, bool* isColliding);
		
	private:
		void _subdivide(SDL_FRect* collider, bool* isColliding);
		void _checkCollisions(SDL_FRect* collider, bool* isColliding);
		static bool _checkIfWithinBounds(SDL_FRect& collider, SDL_FRect& other) ;
		static constexpr int cellCapacity = 4;
		static constexpr int maxDepth = 5;

		int depth;
		SDL_FRect boundary;
		bool isDivided = false;
		bool collideWithPath;

		std::vector<std::unique_ptr<Quadtree>> children;
		std::vector<std::pair<SDL_FRect*, bool*>> colliders;
};


#endif //BROADWAY_SIMULATION_QUADTREE_HPP
