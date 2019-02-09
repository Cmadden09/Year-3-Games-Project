#pragma once
/*============================================================================ =
boundingVolume
Author : Chloe Madden(B00286864)
============================================================================ =*/

class boundingVolume
{
public:
	boundingVolume() {};

	virtual void update(glm::vec3 worldPos) = 0;

};
