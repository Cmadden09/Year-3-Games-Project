/*============================================================================ =
RayCastTestComponent
Author : Chloe Madden(B00286864)
============================================================================ =*/
#include "rayCastTestComponent.h"
#define DEG_TO_RADIAN 0.017453293

RayCastTestComponent::RayCastTestComponent(std::string name)
{
	this->name = name;

	rayMagnitude = 50;

	fireCoolOffTime = 0.2;
	bulletVelocity = 30;

	start = std::clock();
}

RayCastTestComponent::~RayCastTestComponent()
{
	rayMagnitude = 50;
}

void RayCastTestComponent::init()
{

}

void RayCastTestComponent::update(double dt)
{
	glm::vec3 userPos = this->getUser()->getPosition();
	deltaTime = (std::clock() - start) / (double)CLOCKS_PER_SEC;


	if (deltaTime > fireCoolOffTime)
	{

		if (this->input->keyPressed("R"))
		{

			if (this->input->keyPressed("R"))
			{
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
				Ray blappo = physics->castRay(userPos, rotatedDirectionVector, rayMagnitude);

				//Get all objects in the pathh of the ray
				std::vector<GameObject*> objectCollisions = physics->checkRayCollision(blappo);

				//Find out which collided object is closest to the player
				GameObject* obj = nullptr;

				if (objectCollisions.size() != 0)
					obj = physics->checkClosest(this->getUser(), objectCollisions);

				//Debug - print the closest object name
				if (obj != nullptr)
					std::cout << "closest: " << obj->getName() << std::endl;
				else
					std::cout << "No Collision: " << std::endl;

				//Emit bullet - If its going to hit something, set the distance so it stops when it hits.
				if (obj != nullptr)
					bulletRender->emit(userPos, rotatedDirectionVector, glm::vec3(bulletVelocity*dt), glm::distance(userPos, obj->getPosition()));
				else
					bulletRender->emit(userPos, rotatedDirectionVector, glm::vec3(bulletVelocity*dt), rayMagnitude);

				start = std::clock();
			}
		}
		bulletRender->updateEmitPosition(userPos);
	}
}

void RayCastTestComponent::setInput(InputSystem * newInput)
{
	input = newInput;
}

void RayCastTestComponent::setPhysics(PhysicsSystem * newPhysics)
{
	physics = newPhysics;
}

void RayCastTestComponent::setRenderer(bulletParticle* newRenderer)
{
	this->bulletRender = newRenderer;
}
