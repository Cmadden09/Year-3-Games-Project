/*============================================================================ =
Enemy AI Component
Author : Chloe Madden(B00286864)
============================================================================ =*/

#include "CollisionSystem.h"



void CollisionSystem::init() 
{

}



void CollisionSystem::collisionCheck(RigidBodyComponent* rigidbody)
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
			if(dynamicBodies[i] != rigidbody)							//make sure it doesn't test against itself or it will warp speed us far away...
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
		std::cout << "CollisionSystem/collisionCheck: Unsupported or invalid boundingtype" << std::endl;
	}

	
	rigidbody->prevPosition = currentPosition;
		
	
}


void CollisionSystem::collisionReaction(RigidBodyComponent* rigidbody)
{
	glm::vec3 currentPosition = rigidbody->getUser()->getPosition();


	glm::vec3 translationVector = (currentPosition - rigidbody->prevPosition) * glm::vec3(-2.5);

	translationVector = (currentPosition - rigidbody->prevPosition);

	rigidbody->getUser()->setPosition(currentPosition + translationVector * glm::vec3(-2));


}

void CollisionSystem::displacementReaction(RigidBodyComponent* rigidbody, glm::vec3 displacementVector)
{
	glm::vec3 currentPosition = rigidbody->getUser()->getPosition();

	rigidbody->getUser()->setPosition(currentPosition + displacementVector);

}











bool CollisionSystem::OBBtoOBB(OBB* box1, OBB* box2 , RigidBodyComponent* rigidbody)
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

				if (minProj1 < maxProj2 && maxProj1 > maxProj2)
				{
					transVec2 = (maxProj2 - minProj1) * axis;
					zOverlap = true;
				}

				if (minProj2 < minProj1 && maxProj1 < maxProj2)
				{
					transVec2 = (maxProj2 - minProj1) * axis;
					zOverlap = true;
				}
			}



			// Axis 2
			if (axi == 4)
			{

				if (maxProj1 > minProj2 && minProj1 < minProj2)
				{
					transVec1 = (maxProj1 - minProj2) * -axis;
					xOverlap = true;
				}

				if (minProj1 < maxProj2 && maxProj1 > maxProj2)
				{
					transVec1 = (maxProj2 - minProj1) * axis;
					xOverlap = true;
				}

				if (minProj2 < minProj1 && maxProj1 < maxProj2)
				{	
					transVec1 = (maxProj2 - minProj1) * axis;
					xOverlap = true;	
				}

			}

		
			//Axis 3 
			if (axi == 5)
			{
				if (maxProj1 > minProj2 && minProj1 < minProj2)
				{
					transVec3 = (maxProj1 - minProj2) * -axis;
					yOverlap = true;
				}

				if (minProj1 < maxProj2 && maxProj1 > maxProj2)
				{
					transVec3 = (maxProj2 - minProj1) * axis;
					yOverlap = true;
				}

				if (minProj2 < minProj1 && maxProj1 < maxProj2)
				{
					transVec3 = (maxProj2 - minProj1) * axis;
					yOverlap = true;
				}

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

			///std::cout << "Vector 1: ";
			///std::cout << "(" << transVec1.x << ", " << transVec1.y << ", " << transVec1.z << ")" << std::endl;

			///std::cout << "Vector 2: ";
			///std::cout << "(" << transVec2.x << ", " << transVec2.y << ", " << transVec2.z << ")" << std::endl;*/

			displacementReaction(rigidbody, displacementVector);
		}
		
	

	return false;
}



















bool CollisionSystem::AABBtoAABB(AABB* box1, AABB* box2)
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



bool CollisionSystem::OBBtoAABB(OBB* box1, AABB* box2)
{


	return false;
}



void CollisionSystem::addStaticBody(RigidBodyComponent* rigidbody)
{
	staticBodies.push_back(rigidbody);
}

void CollisionSystem::addDynamicBody(RigidBodyComponent* rigidbody)
{
	dynamicBodies.push_back(rigidbody);
}





