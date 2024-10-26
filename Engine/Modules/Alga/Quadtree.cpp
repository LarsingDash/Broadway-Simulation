//
// Created by larsv on 26/10/2024.
//

#include "Quadtree.hpp"
#include <array>

Quadtree::Quadtree(int depth, bool collideWithPath, int x, int y, int width, int height) :
		depth(depth), collideWithPath{collideWithPath}, boundary{
		static_cast<float>(x), static_cast<float>( y),
		static_cast<float>(width), static_cast<float>(height)},
		children{}, colliders{} {}

void Quadtree::render(RenderingModule& renderingModule) const { // NOLINT(*-no-recursion)
	renderingModule.drawRectangleF(boundary, true);
	if (isDivided)
		for (const auto& child: children)
			child->render(renderingModule);
}

void Quadtree::addCollider(SDL_FRect* collider, bool* isColliding) { // NOLINT(*-no-recursion)
	//Redirect to next tree if this one is already subdivided
	if (isDivided) {
		//Find the tree this item corresponds to, and add it there
		for (const auto& child: children) {
			if (_checkIfWithinBounds(*collider, child->boundary)) {
				child->addCollider(collider, isColliding);
				return;
			}
		}

		//Just return in case no matching subtree was found (error case)
		return;
	}

	//Subdivide this cell if there's no more room
	if (depth < maxDepth && colliders.size() > cellCapacity) {
		_subdivide(collider, isColliding);
		return;
	}

	//Check if a collider has been given, meaning collision should be checked
	if (isColliding != nullptr) _checkCollisions(collider, isColliding);

	//Add collider to this cell
	colliders.emplace_back(collider, isColliding);
}

void Quadtree::_subdivide(SDL_FRect* collider, bool* isColliding) { // NOLINT(*-no-recursion)
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
				collideWithPath,
				childNode.x,
				childNode.y,
				childNode.w,
				childNode.h)
		);

		//Loop through colliders and add them to the tree if they overlap
		for (const auto& [otherCollider, otherIsColliding]: colliders)
			if (_checkIfWithinBounds(*otherCollider, nextTree->boundary))
				nextTree->addCollider(otherCollider, otherIsColliding);

		//Check if the collider that was attempted to be added fits here
		if (_checkIfWithinBounds(*collider, nextTree->boundary))nextTree->addCollider(collider, isColliding);
	}

	//Clear this node's child list
	colliders.clear();
}

void Quadtree::_checkCollisions(SDL_FRect* collider, bool* isColliding) {
	//Loop given collider through all colliders in this cell
	for (const auto& [other, otherIsColliding]: colliders) {
		//Check if collider was a tile (no isCollider bool), if so: check CollideWithPat
		if (otherIsColliding || collideWithPath)
		//Check overlap
		if (_checkIfWithinBounds(*collider, *other)) {
			*isColliding = true;
			if (otherIsColliding) *otherIsColliding = true;
		}
	}
}

bool Quadtree::_checkIfWithinBounds(SDL_FRect& collider, SDL_FRect& other) {
	return collider.x < other.x + other.w && //left of cur before right of other
		   collider.x + collider.w > other.x && //right of cur after left of other
		   collider.y < other.y + other.h && //top cur before bottom of other
		   collider.y + collider.h > other.y; //bottom of cur after top of other
}
