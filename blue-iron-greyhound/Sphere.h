#pragma once
/*============================================================================ =
Sphere
Author : Chloe Madden(B00286864)
============================================================================ =*/

#include "glm\glm.hpp"
#include "boundingVolume.h"

class Sphere : public boundingVolume
{
public:
	Sphere(glm::vec3 center, float radius)
	{
		this->center = center;
		this->radius = radius;
	}
	void update(glm::vec3 worldPos){}
	glm::vec3 getp1();
	glm::vec3 getp2();

	
private:
	glm::vec3 center;
	float radius;


};