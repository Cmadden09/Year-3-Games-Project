/*=============================================================================
Enemy AI Component
Author : Chloe Madden(B00286864)
=============================================================================*/

#include "EnemyAIComponent.h"


//temp debug function
void printPath(std::vector<glm::vec3> path)
{

	for (int i = 0; i < path.size(); i++)
	{
		std::cout << i << ":	" << path[i].x << ", " << path[i].y << ", " << path[i].z << ", " << std::endl;
	}
	
	std::cout  << std::endl;
	std::cout  << std::endl;
}

EnemyAIComponent::EnemyAIComponent()
{
	velocity = glm::vec3(0, 0, 0);	
}


void EnemyAIComponent::init()
{
	//Pick one of the targets
	targetIndex = 0;

	//Set currentRoute[0] as the first destination to head to 
	goalNodeIndex = 0;

	//Not at the final destination of currentRoute
	atFinalDestination = false;
}


void EnemyAIComponent::setTargets(std::vector<glm::vec3> targetList)
{
	targets = targetList;

	//Keep track of current goal position
	currentGoalPosition = targets[targetIndex];
}

void EnemyAIComponent::faceDestination(glm::vec3 pos, glm::vec3 dest)
{

	//Calculates angle and set player rotation
	//Really just an up vector 
	glm::vec3 playerVec(0, 1, 0);

	//Calculate rotation in degrees
	glm::vec3 facingVector = dest - pos;

	float angleInDegrees_ = atan2(facingVector.y, facingVector.x) - atan2(playerVec.y, playerVec.x);
	angleInDegrees_ = glm::degrees(angleInDegrees_);

	//Set GameObjects rotation
	this->user->setRotationDegrees(angleInDegrees_ + 90);
}

void EnemyAIComponent::update(double dt)
{
	///debug
	//printPath(currentRoute);
	///

	//If no where to go is defined then don't bother continuing
	if (targets.size() == 0)
		return;


	glm::vec3 currPosition = this->getUser()->getPosition();



	//Stops vector subscript out of range errors
	if (goalNodeIndex > currentRoute.size() - 1)
		goalNodeIndex = 0;

	


	//Recalculate route with new target if there's no route to follow
	while (currentRoute.size() == 0 )
	{
		goalNodeIndex = 0;
		targetIndex++;

		if (targetIndex >= targets.size() - 1)
			targetIndex = 0;

		currentGoalPosition = targets[targetIndex];

		glm::vec2 pos(currPosition.x, currPosition.z);
		glm::vec2 goal(currentGoalPosition.x, currentGoalPosition.z);

		currentRoute = AIsystem->findPath(pos, goal);
	}
		

	//if not at last node in the current path
	if (!atFinalDestination)
	{
		// If still travelling to next position
		if (glm::distance(currPosition, currentRoute[goalNodeIndex]) > 1) 
		{
			velocity = glm::normalize(currentRoute[goalNodeIndex] - currPosition);
			velocity *=  15 * dt;
		}
		else
		{
			//If at the position of the last node in the current path
			if (glm::distance(currPosition, currentRoute[currentRoute.size()-1]) < 1 )
			{
				atFinalDestination = true;
				velocity = glm::vec3(0);
			}
			else//else start heading towards the next part of 'CurrentRoute'
			{
				goalNodeIndex++;

			
			}
		
		}
			
	}
	else//Else we have reached the final position of 'CurrentRoute'
	{

		// Decide where the next goal lies. Should simply
		//Loop this but write and algorithm deciding what to do/where to go
		targetIndex++;

		
		//Reset target index if out of range
		if (targetIndex > targets.size() - 1)
			targetIndex = 0;

		currentGoalPosition = targets[targetIndex];

		//Generate a new route using the AI System
		glm::vec2 pos(currPosition.x, currPosition.z);
		glm::vec2 goal(currentGoalPosition.x, currentGoalPosition.z);

		currentRoute = AIsystem->findPath(pos, goal);


		//Resets
		atFinalDestination = false;
		goalNodeIndex = 0;

	}
		
	//update player movement
	this->getUser()->setPosition(currPosition + velocity);


	//Turn togace direction of travel
	faceDestination(currPosition, currentRoute[goalNodeIndex]);

	
}



void EnemyAIComponent::setAIsystem(AISystem* ai)
{
	AIsystem = ai;
}

