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
	visited.clear();
}

void PathfindingModule::setPathfindingType(PathfindingModule::PathfindingType type) {
	pathfindingType = type;
	_recalculatePath();
}
void PathfindingModule::toggleRenderPath() { renderPath = !renderPath; }
void PathfindingModule::toggleRenderVisited() { renderVisited = !renderVisited; }
bool PathfindingModule::getRenderPath() const { return renderPath; }
bool PathfindingModule::getRenderVisited() const { return renderVisited; }
std::vector<Tile *> PathfindingModule::getPath() const {return path;}

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
	//Init the queue for looping through neighbors in a fifo manner, this will cause Breadth-First
	std::queue<Tile*> queue{};
	//Init the map for reconstructing the path afterward
	std::unordered_map<Tile*, Tile*> lookup;
	
	//Add the start to the queue and visited
	queue.push(start);
	visited.insert(start);
	lookup[start] = nullptr;

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
				//Add new neighbor to the lookup table
				lookup[*neighbor] = current;
				
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
	
	//Print amount of steps if target was found, cancel reconstruction if not
	if (lookup.find(target) == lookup.cend()) return;
	std::cout << "BFS visited " << visited.size() << " tiles" << std::endl;
	
	//Go through the lookup table to retrace the steps, reconstructing the path
	Tile* current = lookup[target];
	while (current != nullptr && current != start) {
		path.push_back(current);
		current = lookup[current];
	}
}

void PathfindingModule::_dijkstra() {

}



