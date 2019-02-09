#pragma once
/*============================================================================ =
RigidBodyComponent
Author : Chloe Madden(B00286864)
============================================================================ =*/
#include "Component.h"
#include "glm\glm.hpp"
#include "boundingVolume.h"
#include "AABB.h"
#include "Sphere.h"
#include "OBB.h"
#include "PhysicsSystem.h"



class RigidBodyComponent : public Component
{
public:
	RigidBodyComponent(string name);
	~RigidBodyComponent();

	void createAABB(glm::vec3 min, glm::vec3 max);
	void createSphere(glm::vec3 center, float radius);
	void createOBB(glm::vec3 min, glm::vec3 max);

	void setboundingVolume(glm::vec3 p1, glm::vec3 p2);
	

	string getBodyType();
	string getBoundingType();
	boundingVolume* getBoundingVolume();  
	void setBodyType(string bodytype);
	void setBoundingType(string boundtype);
	bool isInit();

	void init();
	void update(double dt);

	void setCollisionSystem(PhysicsSystem* collisionSys);

	glm::vec3 prevPosition;
private:
	bool isInitialised;
	bool isAsleep;

	PhysicsSystem* collisionSystem;

	string bodyType;    //dynamic or static
	string boundingType;

	boundingVolume* boundingVolume;
	
};
