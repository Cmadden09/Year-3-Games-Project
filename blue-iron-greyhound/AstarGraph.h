#pragma once
/*=============================================================================
AstarGraph
Author : Chloe Madden(B00286864)
=============================================================================*/
/*
This class represent the entire pathway map for a scene. It represents this using nodes.
The nodes store information on their position, paths and path weights.
*/
#include "node.h"
#include <iostream>


class AstarGraph
{
public:
	AstarGraph(int name[], glm::vec2 location[], std::pair<int, int>edge_array[], float weights[], int numOfNodes, int numEdges)
	{
		numGraphNodes = numOfNodes;

		//for (int h = 0; h < numGraphNodes; h++)
		//	nodes.push_back(nullptr);

		int edge_array_size = numEdges;

		//create nodes
		for (int i = 0; i < numGraphNodes; i++)
		{
			nodes.push_back(node(name[i], location[i]));

			//find all paths to and from current node
			for (int j = 0; j < edge_array_size; j++)
			{

				if (nodes[i].getName() == edge_array[j].first)
				{
					nodes[i].addPath(edge_array[j], weights[j]);
				}

				if (nodes[i].getName() == edge_array[j].second)
				{
					nodes[i].addPath(edge_array[j], weights[j]);
				}

			}
		}
	}

	void printDetails()
	{
		for (int i = 0; i < numGraphNodes; i++)
		{
			std::cout << "Node ID: " << nodes[i].getName() << "	" << nodes[i].getPos().x << ", " << nodes[i].getPos().y << std::endl;

			for (int j = 0; j < nodes[i].counter; j++)
			{
				std::cout << "Path:	" << nodes[i].pathWays[j].first << ", " << nodes[i].pathWays[j].second << "	";
				std::cout << "Weight: " << nodes[i].weights[j] << std::endl;

			}

		}
	}

	~AstarGraph()
	{

	}


	std::vector<node> nodes;

private:
	int numGraphNodes;



};
