#pragma once
/*=============================================================================
AISystem
Author : Chloe Madden(B00286864)
=============================================================================*/
/*
This class stores a map of pathways. The Enemy AI Component can use this system 
to find routes around the map. This system uses the A* algorithm to calculate 
the shortest path.
*/


#include "System.h"
#include "AstarGraph.h"
#include "aStarPathFinder.h"


class AISystem : public System
{
public:
	AISystem();
	~AISystem() {}

	void init();
	void addPathGraph(AstarGraph* graph);
	
	std::vector<glm::vec3> findPath(glm::vec2 currPos, glm::vec2 target);

private:
	AstarGraph* mapPath;
	aStarPathFinder AstarAlgorithm;
};