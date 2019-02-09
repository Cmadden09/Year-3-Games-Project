#include "AIMechanicsComponent.h"
#include "RigidBodyComponent.h"

AIMechanicsComponent::AIMechanicsComponent(std::string name)
{
	this->name = name;
	this->spawnPos = glm::vec3(0);
	this->score = 0;
}


void AIMechanicsComponent::init()
{
	this->health = 100;
	this->damage = 5;
	this->weaponRange = 40;
	this->rateOfFire = 1;
	this->cooldownTimer = 0;
	this->awaitingRespawn = false;


	velocity = glm::vec3(0, 0, 0);
	previousPos = glm::vec3(10);


	//Pick one of the targets
	targetIndex = 0;

	//Keep track of current goal position
	currentGoalPosition = targets[targetIndex];

	//Set currentRoute[0] as the first destination to head to 
	goalNodeIndex = 0;


	//Not at the final destination of currentRoute
	atFinalDestination = false;

	if (this->getUser())
	{
		this->getUser()->setPosition(this->spawnPos);

		//Reset Route
		currentRoute = AIsystem->findPath(this->spawnPos, currentGoalPosition);
	}
}

void AIMechanicsComponent::addTargets(std::vector<glm::vec3> targets)
{
	this->targets = targets;
}

void AIMechanicsComponent::update(double dt)
{
	cooldownTimer += dt;

	if (this->health <= 0)
	{
		this->user->isAlive = false;
		//std::cout << this->user->getName() << " Is Dead!" << std::endl; //Testing
	}
	attack(dt);
	move(dt);
}



void AIMechanicsComponent::setAIsystem(AISystem* ai)
{
	AIsystem = ai;
}

void AIMechanicsComponent::fireWeapon(double dt)
{
	int bulletVelocity = 100;


	//Calculate the rays direction
	glm::vec3 forward(0, 0, -1);
	glm::vec3 up(0, 1, 0);

	//double theta = (this->getUser()->getRotationDegrees()* DEG_TO_RADIAN);	//The minus was an attempt to fix the collision inaccuracy
	//double theta = -(this->getUser()->getRotationDegrees()* DEG_TO_RADIAN) + 135 * DEG_TO_RADIAN;
	double theta = (-((this->getUser()->getRotationDegrees()* DEG_TO_RADIAN) *2 ) -90 * DEG_TO_RADIAN);

	double cos_thetaf = cos(theta);
	glm::vec3 cos_theta(cos(theta));
	glm::vec3 sin_theta(sin(theta));

	glm::dvec3 rotatedDirectionVector = (forward * cos_theta) + (glm::cross(up, forward) * sin_theta) + (up * glm::dot(up, forward)) * glm::vec3((1 - cos_thetaf));
	rotatedDirectionVector = glm::vec3(rotatedDirectionVector.x, rotatedDirectionVector.y, -rotatedDirectionVector.z);

	//Find the two points defining our ray 
	Ray weaponRay = physics->castRay(this->getUser()->getPosition(), rotatedDirectionVector, weaponRange);

	//Get all objects in the path of the ray
	std::vector<GameObject*> potentialHits = physics->checkRayCollision(weaponRay);

	//Find out which collided object is closest to the player
	GameObject* obj = nullptr;

	if (potentialHits.size() != 0)
		obj = physics->checkClosest(this->getUser(), potentialHits);

	//Debug - print the closest object name
	if (obj != nullptr)
	{
		

		MechanicsComponent * comp = obj->getComponent<MechanicsComponent>();
		if (comp != nullptr)
		{
			comp->setHealth(comp->getHealth() - this->damage);
			if (comp->getHealth() <= 0)
				this->score++;
			
			//Debug:
			//std::cout << "closest: " << obj->getName() << std::endl;
			//std::cout << comp->getUser()->getName() << "health: " << comp->getHealth();
		}
	}

	//Emit bullet - If its going to hit something, set the distance so it stops when it hits.
	if (obj != nullptr)
		particleRenderer->emit(this->getUser()->getPosition(), rotatedDirectionVector, glm::vec3(bulletVelocity*dt), glm::distance(this->getUser()->getPosition(), obj->getPosition()));
	else
		particleRenderer->emit(this->getUser()->getPosition(), rotatedDirectionVector, glm::vec3(bulletVelocity*dt), weaponRange);

	start = std::clock();
}

void AIMechanicsComponent::move(double dt)
{
	glm::vec3 currPosition = this->getUser()->getPosition();


	//Stops vector subscript out of range errors
	if (goalNodeIndex > currentRoute.size() - 1)
		goalNodeIndex = 0;

	//Recalculate route with new target if there's no route to follow
	while (currentRoute.size() == 0)
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
		if (glm::distance(currPosition, currentRoute[goalNodeIndex]) > 0.5)
		{
			velocity = glm::normalize(currentRoute[goalNodeIndex] - currPosition);
			velocity *= 15 * dt;
		}
		else
		{
			//If at the position of the last node in the current path
			if (glm::distance(currPosition, currentRoute[currentRoute.size() - 1]) < 0.5)
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

	//Store position. If AI gets stuck it will change target
	previousPos = currPosition;

}

void AIMechanicsComponent::attack(double dt)
{
	GameObject *target;

	std::vector<RigidBodyComponent*> possibleTargets = physics->getDynamicBodies();
	for (int i = 0; i <= possibleTargets.size() -1; i++)
	{
		RigidBodyComponent *temp = possibleTargets[i];
		std::vector<RigidBodyComponent*> inRangeTargets;

		if (temp->getUser() != this->getUser())
		{
			float dist = sqrt((((this->user->getPosition().x - temp->getUser()->getPosition().x) * (this->user->getPosition().x - temp->getUser()->getPosition().x)) +
				((this->user->getPosition().y - temp->getUser()->getPosition().y) * (this->user->getPosition().y - temp->getUser()->getPosition().y)) +
				((this->user->getPosition().z - temp->getUser()->getPosition().z) * (this->user->getPosition().z - temp->getUser()->getPosition().z))));

			if (dist <= weaponRange - 5)
			{
				glm::vec3 AIVec = this->user->getPosition() - temp->getUser()->getPosition();
				glm::vec2 playerVec(0, 1);

				double angleInDegrees = atan2(AIVec.x, AIVec.z) - atan2(playerVec.y, playerVec.x);
				angleInDegrees = glm::degrees(angleInDegrees);
				//this->user->setRotationDegrees(angleInDegrees + 180);
				this->user->setRotationDegrees(((angleInDegrees)*0.5) - 90);

				if (cooldownTimer > rateOfFire)
				{
					audio->playAudio("../../assets/audio/Laser-whiplash-01.wav", false, this->user->getPosition(),this->thePlayer->getPosition());
					fireWeapon(dt);
					cooldownTimer = 0;
				}
			}	
		}
	}
}

