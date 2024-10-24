//
// Created by larsv on 24/10/2024.
//

#include "PathfindingModule.hpp"

PathfindingModule::PathfindingModule(Museum& mus) : museum{mus} {}

void PathfindingModule::setStart(Tile* s) {
	start = s;
	_recalculatePath();
}

void PathfindingModule::setTarget(Tile* t) {
	target = t;
	_recalculatePath();
}

void PathfindingModule::reset() {
	start = nullptr;
	target = nullptr;
	path.clear();
}

void PathfindingModule::setPathfindingType(PathfindingModule::PathfindingType type) { pathfindingType = type; }
void PathfindingModule::toggleRenderPath() { renderPath = !renderPath; }
void PathfindingModule::toggleRenderVisited() { renderVisited = !renderVisited; }

void PathfindingModule::_recalculatePath() {
	switch (pathfindingType) {
		default:
		case BreathFirstSearch:
			_breathFirstSearch();
			break;
		case Dijkstra:
			_dijkstra();
			break;
	}
}

void PathfindingModule::_breathFirstSearch() {

}

void PathfindingModule::_dijkstra() {

}
