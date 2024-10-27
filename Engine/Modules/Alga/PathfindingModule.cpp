//
// Created by larsv on 24/10/2024.
//

#include "PathfindingModule.hpp"
#include <queue>
#include <algorithm>

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
    //Priority queue om waardes automatisch op te slaan op volgorde van grootste naar kleinste waarde
    using TileCostPair = std::pair<float, Tile*>;
    std::priority_queue<TileCostPair, std::vector<TileCostPair>, std::greater<TileCostPair>> priorityQueue;

    // Distance mappen om de afstand van de start naar elke tile bij te houden
    std::unordered_map<Tile*, float> distance;
    std::unordered_map<Tile*, Tile*> predecessors;

    // Alle onbezochte tiles op infinity zetten
    for (const auto& row : museum.grid) {
        for (const auto& tilePtr : row) {
            distance[tilePtr.get()] = std::numeric_limits<float>::infinity();
        }
    }
    //start tile op 0 zetten
    distance[start] = 0.0f;

    // Start tile in de priority queue zetten als beginpunt
    priorityQueue.emplace(0.0f, start);

    // Dijstkra's algoritme
    // 1. Controleer de tile met de laagste afstand van de start

    while (!priorityQueue.empty()) {
        Tile* current = priorityQueue.top().second;
        float currentCost = priorityQueue.top().first;
        priorityQueue.pop();
        visited.insert(current);
        // 2. Als het doel bereikt is, stop
        if (current == target) break;


        // 3. Loop door alle buren van de tile en bereken de totale afstand die het zou kosten om om de huidige tile te bereiken
        for (Tile* neighbor : current->getNeighbors()) {
            float neighborCost = currentCost + neighbor->currentState->config.second;

            // 4. Als de totale afstand kleiner is dan de huidige afstand, update de afstand en voeg hem toe aan de queu
            if (neighborCost < distance[neighbor]) {
                distance[neighbor] = neighborCost;
                predecessors[neighbor] = current;
                priorityQueue.emplace(neighborCost, neighbor);
            }
        }
    }
    // 5. Bouw het pad terug vanaf de target naar de start
    Tile* current = target;
    while (predecessors.find(current) != predecessors.end()) {
        path.push_back(current);
        current = predecessors[current];
    }
    std::reverse(path.begin(), path.end());

    if (distance[target] != std::numeric_limits<float>::infinity()) {
        std::cout << "Shortest path cost: " << distance[target] << std::endl;
    } else {
        std::cout << "No path found" << std::endl;
    }

}



