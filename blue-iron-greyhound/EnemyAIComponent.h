#pragma once
/*
=============================================================================
Enemy AI Component
Author: Chloe Madden (B00286864)
=============================================================================

This class uses the AI system to navigate as that is where the current graph/map 
of pathways is stored. The member variable 'targets' represenst key positions
in world coordinates. They could include the players position, a defensive position  
or a capture point to defend/attack. Currently the class is just looping through 
these targets.

TO DO
-We will need to define the targets and also write an algorithm that can let 
the AI component decide what to target and when.
-There is code to turn the object towards the target but I'm not sure this is 
100% working
=============================================================================*/


#include "Component.h"
#include "GameObject.h"
#include "AISystem.h"


class EnemyAIComponent : public Component
{
public:
	EnemyAIComponent();
	~EnemyAIComponent() {}

	void init();
	void update(double dt);

	void setAIsystem(AISystem*);

	//Rotate mesh to face direction of travel
	void faceDestination(glm::vec3 pos, glm::vec3 dest);

	void setTargets(std::vector<glm::vec3> targetList);

private:
	//The AI system deals with directing this class. You can pass in any 
	//world space coordinate as a target and it will return a vector of positions 
	//in space which is the shortest route according to it's current map/graph
	AISystem* AIsystem;

	glm::vec3 velocity;

	//A vector of coordinates representing our current journey
	std::vector<glm::vec3> currentRoute;

	//The position in 'currentRoute' that we are currently heading towards
	glm::vec3 currentGoalPosition;

	//Key positions in space that this object and aim for (player, behind cover, 
	std::vector<glm::vec3> targets;

	//returns whether we have arrived at the final position in 'currentRoute'
	bool atFinalDestination;

	//The index to 'currentRoute' for the position that we are currently heading towards
	int goalNodeIndex;

	//The index to 'targets' for the position that we are what to get to
	int targetIndex;



};