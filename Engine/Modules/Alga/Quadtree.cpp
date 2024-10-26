//
// Created by larsv on 26/10/2024.
//

#include "Quadtree.hpp"
#include <array>

Quadtree::Quadtree(int depth, int x, int y, int width, int height) :
		depth(depth), boundary{
		static_cast<float>(x), static_cast<float>( y),
		static_cast<float>(width), static_cast<float>(height)},
		children{}, colliders{} {}

void Quadtree::render(RenderingModule& renderingModule) const { // NOLINT(*-no-recursion)
	renderingModule.drawRectangleF(boundary, true);
	if (isDivided)
		for (const auto& child: children)
			child->render(renderingModule);
}

void Quadtree::addCollider(SDL_FRect* collider) { // NOLINT(*-no-recursion)
	//Redirect to next tree if this one is already subdivided
	if (isDivided) {
		//Find the tree this item corresponds to, and add it there
		for (const auto& child: children) {
			if (child->_checkIfWithinBounds(collider)) {
				child->addCollider(collider);
				return;
			}
		}

		//Just return in case no matching subtree was found (error case)
		return;
	}

	//If there's enough room, add it to this cell, subdivide if not
	if (depth == maxDepth || colliders.size() < cellCapacity)
		colliders.push_back(collider);
	else {
		//Mark this tree as divided
		isDivided = true;

		//Ready boundaries for child trees
		float nextWidth = boundary.w / 2;
		float nextHeight = boundary.h / 2;
		std::array<SDL_FRect, 4> childTrees
				{{
						 {boundary.x, boundary.y, nextWidth, nextHeight},    //TopLeft
						 {boundary.x + nextWidth, boundary.y, nextWidth, nextHeight},    //TopRight
						 {boundary.x, boundary.y + nextHeight, nextWidth, nextHeight},    //BottomLeft
						 {boundary.x + nextWidth, boundary.y + nextHeight, nextWidth, nextHeight},    //BottomRight
				 }};

		for (const auto& childNode: childTrees) {
			//Make sub-quadtree
			std::unique_ptr<Quadtree>& nextTree = children.emplace_back(std::make_unique<Quadtree>(
					depth + 1,
					childNode.x,
					childNode.y,
					childNode.w,
					childNode.h)
			);

			//Loop through colliders and add them to the tree if they overlap
			for (const auto& otherCollider: colliders)
				if (nextTree->_checkIfWithinBounds(otherCollider))
					nextTree->addCollider(otherCollider);

			//Check if the collider that was attempted to be added fits here
			if (nextTree->_checkIfWithinBounds(collider))nextTree->addCollider(collider);
		}

		//Clear this node's child list
		colliders.clear();
	}
}

bool Quadtree::_checkIfWithinBounds(SDL_FRect* collider) const {
	return collider->x < boundary.x + boundary.w && //left of cur before right of other
		   collider->x + collider->w > boundary.x && //right of cur after left of other
		   collider->y < boundary.y + boundary.h && //top cur before bottom of other
		   collider->y + collider->h > boundary.y; //bottom of cur after top of other
}



