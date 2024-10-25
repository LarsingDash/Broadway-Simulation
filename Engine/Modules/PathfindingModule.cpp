//
// Created by larsv on 24/10/2024.
//

#include "PathfindingModule.hpp"
#include <queue>

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

void PathfindingModule::setPathfindingType(PathfindingModule::PathfindingType type) {
	pathfindingType = type;
	_recalculatePath();
}
void PathfindingModule::toggleRenderPath() { renderPath = !renderPath; }
void PathfindingModule::toggleRenderVisited() { renderVisited = !renderVisited; }
bool PathfindingModule::getRenderPath() const { return renderPath; }
bool PathfindingModule::getRenderVisited() const { return renderVisited; }

void PathfindingModule::_recalculatePath() {
	//Debug log
	std::cout << "ReCalc path: ";
	if (start) std::cout << start->getPos().x << " - " << start->getPos().y;
	else std::cout << "NULL";
	std::cout << " to ";
	if (target) std::cout << target->getPos().x << " - " << target->getPos().y;
	else std::cout << "NULL";
	std::cout << std::endl;

	//Clear lists
	path.clear();
	visited.clear();

	//Don't pathfind if there's no start, target or if the start and target are the same 
	if (!start || !target || (start == target)) return;
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
	//Initialize the queue and add the start (also to the visited set)
	std::queue<Tile*> queue{};
	queue.push(start);
	visited.insert(start);

	//Extra condition for early return if the path is found
	bool targetFound = false;

	//Keep going till queue is either empty or target is found (early return)
	while (!queue.empty() && !targetFound) {
		//Get current from dequeue
		Tile* current = queue.front();

		//Add all neighbors in reverse order
		for (auto neighbor = current->getNeighbors().rbegin();
			 neighbor != current->getNeighbors().rend(); ++neighbor) {
			
			//Try and add the neighbor to the tile, the return.second indicates if it was actually added 
			if (visited.insert(*neighbor).second) {
				//Check if neighbor was the target, break search if so
				if (*neighbor == target) {
					targetFound = true;
					break;
				}
				
				//If not: add neighbor to the queue to continue the search
				queue.push(*neighbor);
			}
		}

		//Remove tile that was just processed
		queue.pop();
	}
}

void PathfindingModule::_dijkstra() {

}
