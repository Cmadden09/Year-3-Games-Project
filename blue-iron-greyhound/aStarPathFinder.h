#pragma once
/*=============================================================================
aStarPathFinder
Author : Chloe Madden(B00286864)
=============================================================================*/
/*
This class runs the A* algorithm for the AI System. Returns a vector of positions
in space (the shortest path between two given positions)
*/
#include "node.h"
#include "AstarGraph.h"
#include <functional>

class aStarPathFinder
{
public:
	aStarPathFinder(){}

	//Euclidean distance calculation (used for the heuristic values)
	float distanceHeuristic(node startNode, node goalNode)
	{
		glm::vec2 start = startNode.getPos();

		glm::vec2 end = goalNode.getPos();

		float dx = start.x - end.x;
		float dy = start.y - end.y;
		return ::sqrt(dx * dx + dy * dy);
	}



	//find the node with the lowest cost ( g() + h() )
	node lowest(std::vector<node> nodes, node goal)
	{
		node currentLowest;

		//Exit if the list is empty
		if (nodes.empty())
			return currentLowest;

		//Start at first node
		currentLowest = nodes[0];
		float currentLowestCost = nodes[0].g + nodes[0].h;

		//compare all nodes leaving the lowest stored
		for (int i = 1; i < nodes.size(); i++)
		{
			nodes[i].f = nodes[i].g + nodes[i].h;

			if (nodes[i].f  < currentLowestCost)
			{
				currentLowest = nodes[i];
				currentLowestCost = nodes[i].f;
			}

		}

		return currentLowest;
	}



	//Test if a node is inside a given vector
	bool isInside(std::vector<node> &list, node node)
	{
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i].getPos() == node.getPos())
				return true;
		}

		return false;
	}

	//Removes node from given list
	bool remove(std::vector<node> &list, node node)
	{
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i].getPos() == node.getPos())
			{
				list.erase(list.begin() + i);
			}
		}

		return false;
	}



	std::vector<node> AStarAlgorithm(AstarGraph graph, int start, int goal)
	{
		//The nodes taken to goal
		std::vector<node> pathToGoal;

		//Nodes visited but not fully expanded
		std::vector<node> openList;

		//Nodes vistited and fully expanded
		std::vector<node> closedList;

		//Node we start off from
		node startNode = graph.nodes[start];

		//End destination
		node goalNode = graph.nodes[goal];

		//Init current node
		node currentNode;


		//Push start node into openlist and set its f()
		startNode.h = distanceHeuristic(startNode, goalNode);
		startNode.f = startNode.h;

		openList.push_back(startNode);


		while (!openList.empty())
		{
			//Take out the node in openList with the lowest f()
			currentNode = lowest(openList, goalNode);

			//	Check if current node is the goal, if so we are done
			//if (&currentNode == &graph.nodes[goal])
			if (currentNode.getPos() == graph.nodes[goal].getPos())
			{
				//Follow the parents all the way back to the start node, now we have our route
				while (graph.nodes[currentNode.getName()].parent != nullptr)
				{
					pathToGoal.push_back(graph.nodes[currentNode.getName()]);
					currentNode = *graph.nodes[currentNode.getName()].parent;

					//if (&currentNode == &graph.nodes[start])
						if (currentNode.getPos() == graph.nodes[start].getPos())
						break;
				}

				//std::cout << "A* Pathfinding Complete: " << std::endl;

				return pathToGoal;
			}


			// Find all nodes connected via paths to our current node
			std::vector<int> successorIDs = currentNode.getSuccessors();

			// This stores the current successors g()
			float current_succ_cost;

			node* successor;

			//	For each successor of current node
			for (int i = 0; i < successorIDs.size(); i++)
			{
				successor = &graph.nodes[successorIDs[i]];

				//	set current successors g() to be its parents + the cost from parent to itself
				current_succ_cost = currentNode.g + successor->getPathWeight(currentNode.getName());

				//If successor is in the openlist
				if (isInside(openList, *successor))
				{
					if (successor->g <= current_succ_cost)		goto LOOP;

				}//If successor is in the closedList
				else if (isInside(closedList, *successor))
				{
					if (successor->g <= current_succ_cost)      goto LOOP;

					remove(closedList, *successor);
					openList.push_back(*successor);
				}
				else //never encountered this node so put in openList for expansion and init h()
				{
					openList.push_back(*successor);
					successor->h = distanceHeuristic(*successor, goalNode);
				}

				successor->g = current_succ_cost;

				//if(successor.getPos() != currentNode.getPos())
				graph.nodes[successorIDs[i]].parent = &currentNode;

				//successor->parent = &currentNode;
				successor->parent = &graph.nodes[currentNode.getName()];


			LOOP:	std::cout << "";//goto leads here. 
			}

			//currentNode has been fully expanded and can now be moved to closedList
			remove(openList, currentNode);
			closedList.push_back(currentNode);


		}//while

		if (currentNode.getPos() != goalNode.getPos())
		{
			std::cout << "A* algorithm failed: Goal node not found" << std::endl;
			return pathToGoal;
		}
	}


	private:



};
