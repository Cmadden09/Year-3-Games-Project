/*============================================================================ =
RayCastTestComponent
Author : Chloe Madden(B00286864)
============================================================================ =*/

#include "RigidBodyComponent.h"
#include "GameObject.h"



RigidBodyComponent::RigidBodyComponent(string name)
{
	this->name = name;
	init();
}


void RigidBodyComponent::init()
{
	prevPosition = glm::vec3(0, 0, 0);
	isAsleep = false;
	isInitialised = false;	
}

boundingVolume* RigidBodyComponent::getBoundingVolume()
{
	return boundingVolume;
}


void RigidBodyComponent::update(double dt)
{

	//If dynamic update the bounding volumes position
	//and check for collisions
	if (bodyType == "DYNAMIC")
	{
		boundingVolume->update(getUser()->getPosition());
		collisionSystem->collisionCheck(this);
	}

}


// sets values for the boudning .  if the bounding volume is a sphere  then one
// point is treated as center and the other point a point on the circumference of the circle
void RigidBodyComponent::setboundingVolume(glm::vec3 p1, glm::vec3 p2)
{
	glm::vec3 pos = getUser()->getPosition();

	if (boundingType == "OBB")
	{
		createOBB(p1, p2);
		boundingVolume->update(pos);
	}
	else if (boundingType == "AABB")
	{
		createAABB(p1, p2);
		boundingVolume->update(pos);
	}
	else if (boundingType == "SPHERE")
	{
		createSphere(p1, glm::distance(p1, p2));
		boundingVolume->update(pos);
	}
	else
	{
		createOBB(p1, p2);
		boundingVolume->update(pos);
	}

	isInitialised = true;
}


void RigidBodyComponent::setCollisionSystem(PhysicsSystem* collisionSys)
{
	collisionSystem = collisionSys;
}

void RigidBodyComponent::createAABB(glm::vec3 min, glm::vec3 max)
{
	boundingType = "AABB";
	boundingVolume = new AABB(min, max);
	isInitialised = true;
}

void RigidBodyComponent::createOBB(glm::vec3 min, glm::vec3 max)
{
	glm::vec3 rotAxis = getUser()->getRotationAxis();
	float degrees = -getUser()->getRotationDegrees();
	glm::vec3 worldSpacePosition = getUser()->getPosition();



	boundingType = "OBB";
	boundingVolume = new OBB(min, max, rotAxis, degrees, worldSpacePosition);
	isInitialised = true;
}



void RigidBodyComponent::createSphere(glm::vec3 center, float radius)
{
	boundingType = "SPHERE";
	boundingVolume = new Sphere(center, radius);
	isInitialised = true;
}


void RigidBodyComponent::setBodyType(string bodytype)
{
	bodyType = bodytype;

	if (bodyType == "DYNAMIC")
	{
		collisionSystem->addDynamicBody(this);
	}
	if (bodyType == "STATIC")
	{
		collisionSystem->addStaticBody(this);
	}
}

void RigidBodyComponent::setBoundingType(string boundtype)
{
	boundingType = boundtype;
}

string RigidBodyComponent::getBodyType()
{
	return bodyType;
}

string RigidBodyComponent::getBoundingType()
{
	return boundingType;
}

bool RigidBodyComponent::isInit()
{
	return isInitialised;
}



RigidBodyComponent::~RigidBodyComponent()
{
	delete boundingVolume;
	delete this;
}

  




