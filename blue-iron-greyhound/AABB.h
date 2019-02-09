#pragma once
/*============================================================================ =
AABB
Author : Chloe Madden(B00286864)
============================================================================ =*/
#include "glm\glm.hpp"
#include "boundingVolume.h"

class AABB : public boundingVolume
{
public:
	AABB(glm::vec3 min, glm::vec3 max)
	{
		objectSpaceMin = min;
		objectSpaceMax = max;
	}

	void update(glm::vec3 worldPos)
	{
		worldSpaceMin = objectSpaceMin + worldPos;
		worldSpaceMax = objectSpaceMax + worldPos;
	}

	glm::vec3 objectSpaceMin;
	glm::vec3 objectSpaceMax;

	glm::vec3 worldSpaceMin;
	glm::vec3 worldSpaceMax;
private:
	
	
};
