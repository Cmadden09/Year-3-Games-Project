#include "PlayerMechanicsComponent.h"

PlayerMechanicsComponent::PlayerMechanicsComponent(std::string name)
{
	this->name = name;
	this->spawnPos = glm::vec3(0, 0, 0);
	this->score = 0;
}

PlayerMechanicsComponent::~PlayerMechanicsComponent()
{

}

void PlayerMechanicsComponent::init()
{
	this->health = 100;
	this->damage = 20;
	this->weaponRange = 40;
	this->rateOfFire = 0.1;
	this->cooldownTimer = 0;
	this->awaitingRespawn = false;

	if(this->getUser())
		this->getUser()->setPosition(this->spawnPos);
}

void PlayerMechanicsComponent::update(double dt)
{
	cooldownTimer += dt;

	if (this->health <= 0)
	{
		this->user->isAlive = false;
	}
	

	//SHOOTING INPUT IS NOW BEING DONE IN MAIN BY THE LEFT MOUSE
	//The
	///Check for input... Change input to mouse click once inputsystem is updated.
	///if (this->input->keyPressed("R"))
	///{
	///	if (cooldownTimer > rateOfFire)
	///	{
	///		fireWeapon(dt);
	///		cooldownTimer = 0;
	///	}	
	///}	

	//Check for input... Change input to mouse click once inputsystem is updated.
	///if (this->input->mousePressLeft())
	///{
	///	if (cooldownTimer > rateOfFire)
	///	{
	///		fireWeapon(dt);
	///		cooldownTimer = 0;
	///	}
	///}



	
}


void PlayerMechanicsComponent::fireWeapon(double dt)
{

	if (cooldownTimer > rateOfFire)
	{
		

		//printf("Shooty Shooty! \n"); //Testing
		///audio->playAudio("../../assets/audio/Laser-whiplash-01.wav");

		int bulletVelocity = 100;


		//Calculate the rays direction
		glm::vec3 forward(0, 0, -1);
		glm::vec3 up(0, 1, 0);

		double theta = (this->getUser()->getRotationDegrees()* DEG_TO_RADIAN);	//The minus was an attempt to fix the collision inaccuracy

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


		cooldownTimer = 0;
	}
}
