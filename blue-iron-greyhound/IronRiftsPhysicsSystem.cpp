/*============================================================================ =
IronRiftsPhysicsSystem
Author : Chloe Madden(B00286864)
============================================================================ =*/

#include "IronRiftsPhysicsSystem.h"
#include "RigidBodyComponent.h"
#include "openglRenderer.h"

IronRiftsPhysicsSystem::IronRiftsPhysicsSystem()
{
}

void IronRiftsPhysicsSystem::init()
{
}

void IronRiftsPhysicsSystem::draw()
{

}



void IronRiftsPhysicsSystem::collisionCheck(RigidBodyComponent* rigidbody)
{

	glm::vec3 currentPosition = rigidbody->getUser()->getPosition();


	if (rigidbody->getBoundingType() == "AABB")
	{
		AABB* bound = (AABB*)rigidbody->getBoundingVolume();

		//test against all static bodies
		for (unsigned int i = 0; i < staticBodies.size(); i++)
		{
			if (staticBodies[i]->getBoundingType() == "AABB")
				if (AABBtoAABB(bound, (AABB*)staticBodies[i]->getBoundingVolume()))
				{
					collisionReaction(rigidbody);
				}
		}

		//test against all other dynamic bodies bodies
		for (unsigned int i = 0; i < dynamicBodies.size(); i++)
		{
			if (dynamicBodies[i] != rigidbody)							//make sure it doesn't test against itself or it will warp speed us far away...
				if (dynamicBodies[i]->getBoundingType() == "AABB")
					if (AABBtoAABB(bound, (AABB*)dynamicBodies[i]->getBoundingVolume()))
					{
						collisionReaction(rigidbody);
					}
		}
	}
	else if (rigidbody->getBoundingType() == "OBB")
	{
		OBB* bound = (OBB*)rigidbody->getBoundingVolume();

		//test against all static bodies
		for (unsigned int i = 0; i < staticBodies.size(); i++)
		{
			if (staticBodies[i]->getBoundingType() == "AABB")
				if (OBBtoAABB(bound, (AABB*)staticBodies[i]->getBoundingVolume()))
				{
					collisionReaction(rigidbody);
				}

			if (staticBodies[i]->getBoundingType() == "OBB")
				if (OBBtoOBB(bound, (OBB*)staticBodies[i]->getBoundingVolume(), rigidbody))
				{
					collisionReaction(rigidbody);
				}
		}

		//test against all other dynamic bodies bodies
		for (unsigned int i = 0; i < dynamicBodies.size(); i++)
		{
			if (dynamicBodies[i] != rigidbody)
				if (dynamicBodies[i]->getBoundingType() == "AABB")
					if (OBBtoAABB(bound, (AABB*)dynamicBodies[i]->getBoundingVolume()))
					{
						collisionReaction(rigidbody);
					}
			if (dynamicBodies[i] != rigidbody)
				if (dynamicBodies[i]->getBoundingType() == "OBB")
					if (OBBtoOBB(bound, (OBB*)dynamicBodies[i]->getBoundingVolume(), rigidbody))
					{
						collisionReaction(rigidbody);
					}
		}
	}
	else
	{
		std::cout << "IronRiftsPhysicsSystem/collisionCheck: Unsupported or invalid boundingtype" << std::endl;
	}


	rigidbody->prevPosition = currentPosition;


}


void IronRiftsPhysicsSystem::collisionReaction(RigidBodyComponent* rigidbody)
{
	glm::vec3 currentPosition = rigidbody->getUser()->getPosition();


	glm::vec3 translationVector = (currentPosition - rigidbody->prevPosition) * glm::vec3(-2.5);

	translationVector = (currentPosition - rigidbody->prevPosition);

	rigidbody->getUser()->setPosition(currentPosition + translationVector * glm::vec3(-2));


}

glm::vec3 IronRiftsPhysicsSystem::collisionDirectionVector(RigidBodyComponent* rigidbody)
{
	glm::vec3 currentPosition = rigidbody->getUser()->getPosition();

	glm::vec3 translationVector = (currentPosition - rigidbody->prevPosition) * glm::vec3(-2.5);

	translationVector = (currentPosition - rigidbody->prevPosition);

	return translationVector;


}

void IronRiftsPhysicsSystem::displacementReaction(RigidBodyComponent* rigidbody, glm::vec3 displacementVector)
{
	glm::vec3 currentPosition = rigidbody->getUser()->getPosition();

	rigidbody->getUser()->setPosition(currentPosition + displacementVector);

}













bool IronRiftsPhysicsSystem::OBBtoOBB(OBB* box1, OBB* box2, RigidBodyComponent* rigidbody)
{

	// 1) Project each vertice of each shape onto the given axis of seperation (1 of 6... or 3?)
	// 2) Take the min and max projected point of each shape       
	// 3) If any of these projected min and maxs do not overlap then exit, no intersection found


	float minProj1;
	float maxProj1;

	float minProj2;
	float maxProj2;

	std::vector<glm::vec3> vertices1 = box1->worldVertices;
	std::vector<glm::vec3> vertices2 = box2->worldVertices;

	std::vector<glm::vec3> faces = box2->faceNormals;

	glm::vec3 axis;

	int axi;
	glm::vec3 displacementVector;

	glm::vec3 transVec1;
	glm::vec3 transVec2;
	glm::vec3 transVec3;


	bool xOverlap = false;
	bool yOverlap = false;
	bool zOverlap = false;



	for (axi = 3; axi < 6; axi++)
	{
		minProj1 = 1000;
		maxProj1 = -1000;

		minProj2 = 1000;
		maxProj2 = -1000;


		axis = faces[axi];

		// Project all vertice of A and B onto axis and store the min and max of these values
		for (int j = 0; j < vertices1.size(); j++)
		{
			float dotproduct1 = glm::dot(vertices1[j], axis);

			if (dotproduct1 < minProj1) minProj1 = dotproduct1;
			if (dotproduct1 > maxProj1) maxProj1 = dotproduct1;

		}

		for (int j = 0; j < vertices2.size(); j++)
		{
			float dotproduct2 = glm::dot(vertices2[j], axis);

			if (dotproduct2 < minProj2) minProj2 = dotproduct2;
			if (dotproduct2 > maxProj2) maxProj2 = dotproduct2;
		}



		// Test all projections for overlap and flag that axis as having overlap
		//Axis 1
		if (axi == 3)
		{

			if (maxProj1 > minProj2 && minProj1 < minProj2)
			{
				transVec2 = (maxProj1 - minProj2) * -axis;
				zOverlap = true;
			}
			else if (minProj1 < maxProj2 && maxProj1 > maxProj2)
			{
				transVec2 = (maxProj2 - minProj1) * axis;
				zOverlap = true;
			}
			else if (minProj2 < minProj1 && maxProj1 < maxProj2)
			{
				transVec2 = (maxProj2 - minProj1) * axis;
				zOverlap = true;
			}
			else
				return false;
		}



		// Axis 2
		if (axi == 4)
		{

			if (maxProj1 > minProj2 && minProj1 < minProj2)
			{
				transVec1 = (maxProj1 - minProj2) * -axis;
				xOverlap = true;
			}
			else if (minProj1 < maxProj2 && maxProj1 > maxProj2)
			{
				transVec1 = (maxProj2 - minProj1) * axis;
				xOverlap = true;
			}
			else if (minProj2 < minProj1 && maxProj1 < maxProj2)
			{
				transVec1 = (maxProj2 - minProj1) * axis;
				xOverlap = true;
			}
			else
				return false;

		}


		//Axis 3 
		if (axi == 5)
		{
			if (maxProj1 > minProj2 && minProj1 < minProj2)
			{
				transVec3 = (maxProj1 - minProj2) * -axis;
				yOverlap = true;
			}
			else if (minProj1 < maxProj2 && maxProj1 > maxProj2)
			{
				transVec3 = (maxProj2 - minProj1) * axis;
				yOverlap = true;
			}
			else if (minProj2 < minProj1 && maxProj1 < maxProj2)
			{
				transVec3 = (maxProj2 - minProj1) * axis;
				yOverlap = true;
			}
			else 	
				return false;

		}
	}


	//Overlap on axi' mean a collision
	if ((xOverlap && zOverlap && yOverlap) == true)
	{

		if (glm::length(transVec1) < (glm::length(transVec2) && (glm::length(transVec3))))
		{
			displacementVector = transVec1;
		}
		else if (glm::length(transVec2) < (glm::length(transVec3) && (glm::length(transVec1))))
		{
			displacementVector = transVec2;
		}
		else if (glm::length(transVec3) < (glm::length(transVec2) && (glm::length(transVec1))))
		{
			displacementVector = transVec3;
		}

		///debug
		///std::cout << "Vector 1: ";
		///std::cout << "(" << transVec1.x << ", " << transVec1.y << ", " << transVec1.z << ")" << std::endl;

		///std::cout << "Vector 2: ";
		///std::cout << "(" << transVec2.x << ", " << transVec2.y << ", " << transVec2.z << ")" << std::endl;*/

		displacementReaction(rigidbody, displacementVector);
	}



	return false;
}



















bool IronRiftsPhysicsSystem::AABBtoAABB(AABB* box1, AABB* box2)
{

	glm::vec3 min1 = box1->worldSpaceMin;
	glm::vec3 max1 = box1->worldSpaceMax;

	glm::vec3 min2 = box2->worldSpaceMin;
	glm::vec3 max2 = box2->worldSpaceMax;

	// Collision tests. if any tests are false then theres no intersection.
	if (max1.x < min2.x || min1.x > max2.x)
		return false;
	if (max1.y < min2.y || min1.y > max2.y)
		return false;
	if (max1.z < min2.z || min1.z > max2.z)
		return false;
	else
		return true;

}



bool IronRiftsPhysicsSystem::OBBtoAABB(OBB* box1, AABB* box2)
{


	return false;
}

glm::vec3 IronRiftsPhysicsSystem::RayToOBB(Ray ray, OBB * obb)
{
	float minProj1;
	float maxProj1;

	float minProj2;
	float maxProj2;

	std::vector<glm::vec3> vertices1 = obb->worldVertices;
	std::vector<glm::vec3> faces = obb->faceNormals;

	std::vector<glm::vec3> vertices2;
	vertices2.push_back(ray.endPoint);
	vertices2.push_back(ray.startPoint);


	glm::vec3 axis;
	int axi;

	bool xOverlap = false;
	bool yOverlap = false;
	bool zOverlap = false;

	glm::vec3 displacementVector;

	glm::vec3 transVec1;
	glm::vec3 transVec2;
	glm::vec3 transVec3;


	glm::vec3 rayUp(ray.startPoint.x, ray.startPoint.y + 1, ray.startPoint.z);
	glm::vec3 rayAxis = glm::normalize(glm::cross((rayUp - ray.startPoint), (ray.endPoint - ray.startPoint)));
	bool rayOverlap = false;



	

	for (axi = 0; axi < 3; axi++)
	{
		minProj1 = 1000;
		maxProj1 = -1000;

		minProj2 = 1000;
		maxProj2 = -1000;


		axis = faces[axi];

		// Project all vertice of A and B onto axis and store the min and max of these values
		for (int j = 0; j < vertices1.size(); j++)
		{
			float dotproduct1 = glm::dot(vertices1[j], axis);

			if (dotproduct1 < minProj1) minProj1 = dotproduct1;
			if (dotproduct1 > maxProj1) maxProj1 = dotproduct1;

		}

		for (int j = 0; j < vertices2.size(); j++)
		{
			float dotproduct2 = glm::dot(vertices2[j], axis);

			if (dotproduct2 < minProj2) minProj2 = dotproduct2;
			if (dotproduct2 > maxProj2) maxProj2 = dotproduct2;
		}



		// Test all projections for overlap and flag that axis as having overlap
		//Axis 1
		if (axi == 0)
		{

			if (maxProj1 > minProj2 && minProj1 < minProj2)
			{
				transVec2 = (maxProj1 - minProj2) * axis;
				zOverlap = true;
			}
			else if (minProj1 < maxProj2 && maxProj1 > maxProj2)
			{
				transVec2 = (maxProj2 - minProj1) * axis;
				zOverlap = true;
			}
			else if (minProj2 < minProj1 && maxProj1 < maxProj2)
			{
				transVec2 = (maxProj2 - minProj1) * axis;
				zOverlap = true;
			}
			else
				return glm::vec3(NULL);
		}



		// Axis 2
		if (axi == 1)
		{

			if (maxProj1 > minProj2 && minProj1 < minProj2)
			{
				transVec1 = (maxProj1 - minProj2) * axis;
				xOverlap = true;
			}
			else if (minProj1 < maxProj2 && maxProj1 > maxProj2)
			{
				transVec1 = (maxProj2 - minProj1) * axis;
				xOverlap = true;
			}
			else if (minProj2 < minProj1 && maxProj1 < maxProj2)
			{
				transVec1 = (maxProj2 - minProj1) * axis;
				xOverlap = true;
			}
			else
				return glm::vec3(NULL);

		}

	}


	//Check the seperating axis of the Ray (Axis perpendicular to it)
	minProj1 = 1000;
	maxProj1 = -1000;

	minProj2 = 1000;
	maxProj2 = -1000;


	// Project all vertice of A and B onto axis and store the min and max of these values
	for (int j = 0; j < vertices1.size(); j++)
	{
		float dotproduct1 = glm::dot(vertices1[j], rayAxis);

		if (dotproduct1 < minProj1) minProj1 = dotproduct1;
		if (dotproduct1 > maxProj1) maxProj1 = dotproduct1;

	}

	for (int j = 0; j < vertices2.size(); j++)
	{
		float dotproduct2 = glm::dot(vertices2[j], rayAxis);

		if (dotproduct2 < minProj2) minProj2 = dotproduct2;
		if (dotproduct2 > maxProj2) maxProj2 = dotproduct2;
	}

	if (minProj2 > minProj1 && minProj2 < maxProj1)
	{
		rayOverlap = true;
		transVec3 = (minProj2 - minProj1) * rayAxis;
	}
	else
		return glm::vec3(NULL);
		





	//Overlap on axi' mean a collision
	if ((xOverlap && zOverlap && rayOverlap) == true)
	{
		//Get the shortest displacement distance
		if (glm::length(transVec1) < (glm::length(transVec2) && (glm::length(transVec3))))
		{
			displacementVector = transVec1;
		}
		else if (glm::length(transVec2) < (glm::length(transVec3) && (glm::length(transVec1))))
		{
			displacementVector = transVec2;
		}
		else if (glm::length(transVec3) < (glm::length(transVec2) && (glm::length(transVec1))))
		{
			displacementVector = transVec3;
		}
		else
		{
			displacementVector = glm::vec3(0.01);
		}

		return displacementVector;
	}

	return glm::vec3(NULL);
}

float IronRiftsPhysicsSystem::distance(glm::vec3 pos1, glm::vec3 pos2)
{
	//return sqrt((((pos1.x - pos2.x) * (pos1.x - pos2.x)) + ((pos1.y - pos2.y) * (pos1.y - pos2.y)) + ((pos1.z - pos2.z) * (pos1.z - pos2.z))));
	return (((pos1.x - pos2.x) * (pos1.x - pos2.x)) + ((pos1.y - pos2.y) * (pos1.y - pos2.y)) + ((pos1.z - pos2.z) * (pos1.z - pos2.z)));
}



void IronRiftsPhysicsSystem::addStaticBody(RigidBodyComponent* rigidbody)
{
	staticBodies.push_back(rigidbody);
}

void IronRiftsPhysicsSystem::addDynamicBody(RigidBodyComponent* rigidbody)
{
	dynamicBodies.push_back(rigidbody);
}

















Ray IronRiftsPhysicsSystem::castRay(glm::vec3 origin, glm::vec3 direction, float magnitude)
{
	Ray ray;
	ray.startPoint = origin;
	ray.endPoint = origin + (direction * magnitude);
	return ray;
}

std::vector<GameObject*> IronRiftsPhysicsSystem::checkRayCollision(Ray ray)
{

	std::vector<GameObject*> collisions;
	glm::vec3 collisionDist;
	

	////test against all static bodies
	//for (unsigned int i = 0; i < staticBodies.size(); i++)
	//{
	//	collisionDist = RayToOBB(ray, (OBB*)staticBodies[i]->getBoundingVolume());

	//	if (collisionDist != glm::vec3(NULL))					//If the collision test comes back as null then there is no collision
	//	{
	//		collisions.push_back(staticBodies[i]->getUser());
	//	}
	//
	//}

	//test against all dynamic bodies bodies
	for (unsigned int i = 0; i < dynamicBodies.size() ; i++)
	{
		collisionDist = RayToOBB(ray, (OBB*)dynamicBodies[i]->getBoundingVolume());

		if (collisionDist != glm::vec3(NULL))
		{
			collisions.push_back(dynamicBodies[i]->getUser());
		
		}	
	
	}


	//Every object in the path of the ray
	return collisions;

}





GameObject * IronRiftsPhysicsSystem::checkClosest(GameObject* object, std::vector<GameObject*> objList)
{
	GameObject * returnValue = 0;
	float temp = 999999;

	for(int i = 0; i < objList.size(); i++)
	{
		if (objList[i] != object)
		{
			if (returnValue == 0)
			{
				returnValue = objList[i];
				temp = distance(object->getPosition(), objList[i]->getPosition());
			}
			else if (distance(object->getPosition(), objList[i]->getPosition()) < temp)
			{
				returnValue = objList[i];
				temp = distance(object->getPosition(), objList[i]->getPosition());
			}
		}	
	}
	return returnValue;
}

