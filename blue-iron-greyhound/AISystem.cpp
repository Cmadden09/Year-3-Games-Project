/*=============================================================================
AISystem
Author : Chloe Madden(B00286864)
=============================================================================*/
#include "AISystem.h"


AISystem::AISystem()
{

}



void AISystem::init()
{

}

std::vector<glm::vec3> AISystem::findPath(glm::vec2 currPos, glm::vec2 target)
{
	int startNode;
	int goalNode;

	int closestNode;
	float closestNodeDist = 9999;
	
	// Find cloest start node
	for (int i = 0; i < mapPath->nodes.size(); i++)
	{

		float dist = glm::distance(mapPath->nodes[i].getPos(), currPos);

		if (dist < closestNodeDist)
		{
			closestNode = i;
			closestNodeDist = dist;
		}
	}

	startNode = closestNode;
	closestNodeDist = 9999;

	//find cloest target node
	for (int i = 0; i < mapPath->nodes.size(); i++)
	{
		float dist = glm::distance(mapPath->nodes[i].getPos(), target);

		if (dist < closestNodeDist)
		{
			closestNode = i;
			closestNodeDist = dist;
		}
	}

	goalNode = closestNode;

	std::vector<node> pathway = AstarAlgorithm.AStarAlgorithm(*mapPath, startNode, goalNode);

	std::vector<glm::vec3> path;
	for (int i = pathway.size() - 1; i >= 0; i--)
	{
		glm::vec2 edge = pathway[i].getPos();
		path.push_back(glm::vec3(edge.x, 0, edge.y));
	}

	return path;
}


void AISystem::addPathGraph(AstarGraph* graph)
{
	mapPath = graph;
}