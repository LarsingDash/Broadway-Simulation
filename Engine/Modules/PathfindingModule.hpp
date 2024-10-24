//
// Created by larsv on 24/10/2024.
//

#ifndef BROADWAY_SIMULATION_PATHFINDINGMODULE_HPP
#define BROADWAY_SIMULATION_PATHFINDINGMODULE_HPP

#include "../Tiles/Museum.hpp"
#include <unordered_set>

class PathfindingModule {
	public:
		explicit PathfindingModule(Museum& museum);
		
		void setStart(Tile* start);
		void setTarget(Tile* target);
		void reset();

		enum PathfindingType {
			BreathFirstSearch,
			Dijkstra,
			Count, //ALWAYS KEEP LAST
		};
		static const char* PathfindingTypeItems[];
		
		void setPathfindingType(PathfindingType type);
		void toggleRenderPath();
		void toggleRenderVisited();
		[[nodiscard]] bool getRenderPath() const;
		[[nodiscard]] bool getRenderVisited() const;
		
		std::vector<Tile*> path {};
		std::unordered_set<Tile*> visited {};
	private:
		void _recalculatePath();
		void _breathFirstSearch();
		void _dijkstra();
		
		Museum& museum;
		
		bool renderPath{true};
		bool renderVisited{false};
		
		PathfindingType pathfindingType {PathfindingType::BreathFirstSearch};
		
		Tile* start{nullptr};
		Tile* target{nullptr};
};


#endif //BROADWAY_SIMULATION_PATHFINDINGMODULE_HPP
