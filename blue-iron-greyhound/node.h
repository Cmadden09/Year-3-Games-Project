#pragma once
/*=============================================================================
Node
Author : Chloe Madden(B00286864)
=============================================================================*/
/*
A node represents a vertex/destination in the map pathways 
*/
#include <vector>
#include <glm/glm.hpp>


class node
{
public:
	node(){}
	node(int name, glm::vec2 loc)
	{
		//The identifier and position of the node.
		counter = 0;
		this->name = name;
		this->position = loc;
		//Cost values (g-cost so far, h-heuristic distance to destination, f- toal cost)
		this->g = 0;
		this->h = 0;
		this->f = 0;
		//Parent is undefined at first...
		this->parent = NULL;
	}

	//Adds a pathway to the node...
	void addPath(std::pair<int, int> edge, float weight)
	{
		pathWays[counter] = edge;
		weights[counter] = weight;
		counter++;
	}

	//Returns the index of nodes that this node has paths to...
	std::vector<int> getSuccessors()
	{
		std::vector<int> successorIDs;

		//look at all successor containers
		for (int i = 0; i < counter; i++)
		{
			if (pathWays[i].first == name)
				successorIDs.push_back(pathWays[i].second);
			else if (pathWays[i].second == name)
				successorIDs.push_back(pathWays[i].first);
		}

		return successorIDs;
	}

	//Returns the cost of the path to this nodes parent...
	float parentPathWeight()
	{
		for (int i = 0; i < counter; i++)
		{
			if (pathWays[i].first == parent->name)
			{
				return weights[i];
			}
			else if (pathWays[i].second == parent->name)
			{
				return weights[i];
			}
		}
	}


	std::pair<int, int> parentRoute()
	{
		for (int i = 0; i < counter; i++)
		{
			if (pathWays[i].first == parent->name)
			{
				return pathWays[i];
			}
			else if (pathWays[i].second == parent->name)
			{
				return pathWays[i];
			}
		}
	}


	float getPathWeight(int id)
	{
		for (int i = 0; i < counter; i++)
		{
			if (pathWays[i].first == id)
				return weights[i];
			else if (pathWays[i].second == id)
				return weights[i];
		}
	}

	//Return methods for private veriables:
	int getName() { return name; }
	glm::vec2  getPos() { return position; }

	//Public variables:
	std::pair<int, int> pathWays[5];
	float weights[5];

	//The node which led to this node, i.e. its parent...
	node* parent;

	//Costs...
	float g;
	float h;
	float f;

	int counter;

private:
	//Private variables:
	glm::vec2  position;
	int name;
};