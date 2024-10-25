//
// Created by larsv on 24/10/2024.
//

#include "PathfindingModule.hpp"

const char* PathfindingModule::PathfindingTypeItems[] = {
		"BreadthFirstSearch",
		"Dijkstra",
};

PathfindingModule::PathfindingModule(Museum& mus) : museum{mus} {}

void PathfindingModule::setStart(Tile* s) {
	if (start != s) start = s;
	else start = nullptr;
	_recalculatePath();
}

void PathfindingModule::setTarget(Tile* t) {
	if (target != t) target = t;
	else target = nullptr;
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
bool PathfindingModule::getRenderPath() const { return renderPath; }
bool PathfindingModule::getRenderVisited() const { return renderVisited; }
std::vector<Tile *> PathfindingModule::getPath() const {return path;}

void PathfindingModule::_recalculatePath() {
	std::cout << "ReCalc path: ";
	if (start) std::cout << start->getPos().x << " - " << start->getPos().y;
	else std::cout << "NULL";
	std::cout << " to ";
	if (target) std::cout << target->getPos().x << " - " << target->getPos().y;
	else std::cout << "NULL";
	std::cout << std::endl;

	path.clear();
	visited.clear();

	if (!start || !target) return;
	switch (pathfindingType) {
		default:
		case BreadthFirstSearch:
			_breadthFirstSearch();
			break;
		case Dijkstra:
			_dijkstra();
			break;
	}
}

void PathfindingModule::_breadthFirstSearch() {
	path.push_back(&museum.getTile(start->getPos().x, start->getPos().y + 1));
	path.push_back(&museum.getTile(start->getPos().x, start->getPos().y + 2));
	path.push_back(&museum.getTile(start->getPos().x, start->getPos().y + 3));
	path.push_back(&museum.getTile(start->getPos().x, start->getPos().y + 4));
	path.push_back(&museum.getTile(start->getPos().x, start->getPos().y + 5));
	path.push_back(&museum.getTile(start->getPos().x, start->getPos().y + 6));

	visited.insert(&museum.getTile(start->getPos().x, start->getPos().y + 1));
	visited.insert(&museum.getTile(start->getPos().x, start->getPos().y + 2));
	visited.insert(&museum.getTile(start->getPos().x, start->getPos().y + 3));
	visited.insert(&museum.getTile(start->getPos().x, start->getPos().y + 4));
	visited.insert(&museum.getTile(start->getPos().x, start->getPos().y + 5));
	visited.insert(&museum.getTile(start->getPos().x, start->getPos().y + 6));
}

void PathfindingModule::_dijkstra() {

}



