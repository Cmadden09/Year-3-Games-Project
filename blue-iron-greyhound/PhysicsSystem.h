#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "GameObject.h"
#include "System.h"
#include "AABB.h"
#include "OBB.h"

struct Ray { glm::vec3 startPoint, endPoint; };

class RigidBodyComponent;

class PhysicsSystem : public System
{
public:
	PhysicsSystem() {}
	virtual ~PhysicsSystem() {}

	virtual void init() = 0;

	virtual void addStaticBody(RigidBodyComponent* rigidbody) = 0;
	virtual void addDynamicBody(RigidBodyComponent* rigidbody) = 0;

	virtual void collisionCheck(RigidBodyComponent* rigidbody) = 0;
	virtual void collisionReaction(RigidBodyComponent* rigidbody) = 0;
	virtual void displacementReaction(RigidBodyComponent* rigidbody, glm::vec3 displacementVector) = 0;
	virtual glm::vec3 collisionDirectionVector(RigidBodyComponent* rigidbody) = 0;

	//Raycasting...
	virtual Ray castRay(glm::vec3 startPoint, glm::vec3 direction, float distance) = 0;
	virtual std::vector<GameObject*> checkRayCollision(Ray ray) = 0;
	virtual GameObject* checkClosest(GameObject* object, std::vector<GameObject*> objList) = 0;

	virtual std::vector<RigidBodyComponent*> getStaticBodies() = 0;
	virtual std::vector<RigidBodyComponent*> getDynamicBodies() = 0;
};