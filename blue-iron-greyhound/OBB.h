#pragma once
/*============================================================================ =
OBB
Author : Chloe Madden(B00286864)
============================================================================ =*/
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "boundingVolume.h"
#include <iostream>
//#include "OpenglUtils.h"
#include <vector>




#define DEG_TO_RADIAN 0.017453293
class OBB : public boundingVolume
{
public:
	OBB(glm::vec3 min, glm::vec3 max, glm::vec3 rotAxis, float degrees, glm::vec3 worldSpacePosition);

	void update(glm::vec3 worldPos);

	//Uses the 8 vertices of the box to calculate the 6 face normal vectors. These are for collision testing.
	void calculateSurfaceNormals();	

	// Translates the 8 box vertices by position and rotation
	void updateVertices();		

	// Finds the boxes 8 vertices based on the given min and max of the box (in object space)
	void calculateVertices();		
	
	void setminmax(glm::vec3 min, glm::vec3 max);
	void setGlobalPosition(glm::vec3 pos);
	void setRotation(float degrees, glm::vec3 roatationAxis);
	
	void printDetails();
	void draw();
	
	glm::vec3 objectSpaceMin;
	glm::vec3 objectSpaceMax;

	glm::vec4 rotatedMin;
	glm::vec4 rotatedMax;

	glm::vec3 worldSpaceMin;
	glm::vec3 worldSpaceMax;

	glm::mat4 rotation;

	glm::vec3 position;

	glm::vec3 rotationAxis;
	float degrees;

	OBB* testBox;

	std::vector<glm::vec3> EdgeAxi;
	std::vector<glm::vec3> faceNormals;
	std::vector<glm::vec3> objVertices;

	std::vector<glm::vec3> worldVertices;


private:


};
