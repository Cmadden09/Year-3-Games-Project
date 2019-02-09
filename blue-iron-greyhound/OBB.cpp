/*============================================================================ =
OBB
Author : Chloe Madden(B00286864)
============================================================================ =*/
#include "OBB.h"


OBB::OBB(glm::vec3 min, glm::vec3 max,glm::vec3 rotAxis, float degrees, glm::vec3 worldSpacePosition)
{
	objectSpaceMin = min;
	objectSpaceMax = max;

	calculateVertices();
	position = worldSpacePosition;
	rotationAxis = rotAxis;
	this->degrees = degrees;

	setRotation(degrees, rotAxis);
	updateVertices();
	calculateSurfaceNormals();

	rotationAxis = rotAxis;
	this->degrees = degrees;

}


void OBB::calculateVertices()
{
	//Vertices in object space
	objVertices.push_back(glm::vec3(objectSpaceMin));
	objVertices.push_back(glm::vec3(objectSpaceMin.x, objectSpaceMax.y, objectSpaceMin.z));
	objVertices.push_back(glm::vec3(objectSpaceMin.x, objectSpaceMin.y, objectSpaceMax.z));
	objVertices.push_back(glm::vec3(objectSpaceMin.x, objectSpaceMax.y, objectSpaceMax.z));

	objVertices.push_back(glm::vec3(objectSpaceMax));
	objVertices.push_back(glm::vec3(objectSpaceMax.x, objectSpaceMin.y, objectSpaceMin.z));
	objVertices.push_back(glm::vec3(objectSpaceMax.x, objectSpaceMax.y, objectSpaceMin.z));
	objVertices.push_back(glm::vec3(objectSpaceMax.x, objectSpaceMin.y, objectSpaceMax.z));

	//initialise our world space vertice with the initial object space values. 
	//UpdateVertices() will convert these to world space.
	for (int i = 0; i < objVertices.size(); i++)
	{
		worldVertices.push_back(objVertices[i]);
	}
}

void OBB::updateVertices()
{
	//tranfrom the object space vertices to world space (position and roation applied) and store
	for (int i = 0; i < worldVertices.size(); i++)
	{	
		worldVertices[i] = glm::vec4(objVertices[i], 0) * rotation;
		worldVertices[i] = worldVertices[i] + position;

		if (worldVertices[i].x < worldSpaceMin.x)  worldSpaceMin.x = worldVertices[i].x;
		if (worldVertices[i].y < worldSpaceMin.y)  worldSpaceMin.y = worldVertices[i].y;
		if (worldVertices[i].z < worldSpaceMin.z)  worldSpaceMin.z = worldVertices[i].z;

		if (worldVertices[i].x > worldSpaceMax.x)  worldSpaceMax.x = worldVertices[i].x;
		if (worldVertices[i].y > worldSpaceMax.y)  worldSpaceMax.y = worldVertices[i].y;
		if (worldVertices[i].z > worldSpaceMax.z)  worldSpaceMax.z = worldVertices[i].z;

	
	}

}


void OBB::update(glm::vec3 worldPos)
{
	if (position != worldPos)
	{
		position = worldPos;

		//setRotation(degrees, rotationAxis);
		updateVertices();
		//calculateSurfaceNormals();
	}

}

void OBB::setminmax(glm::vec3 min, glm::vec3 max)
{
	objectSpaceMin = min;
	objectSpaceMax = max;
}


void OBB::setGlobalPosition(glm::vec3 pos)
{
	position = pos;
}



void OBB::calculateSurfaceNormals() 
{
	//If vector not yet initialized
	if (faceNormals.size() < 1)
	{
		//"min" normals (3)
		faceNormals.push_back(glm::cross((worldVertices[2] - worldVertices[0]), (worldVertices[1] - worldVertices[0])));
		faceNormals.push_back(glm::cross((worldVertices[1] - worldVertices[0]), (worldVertices[5] - worldVertices[0])));
		faceNormals.push_back(glm::cross((worldVertices[5] - worldVertices[0]), (worldVertices[2] - worldVertices[0])));

		//"max" normals (3)
		faceNormals.push_back(glm::cross((worldVertices[2] - worldVertices[4]), (worldVertices[7] - worldVertices[4])));
		faceNormals.push_back(glm::cross((worldVertices[7] - worldVertices[4]), (worldVertices[5] - worldVertices[4])));
		faceNormals.push_back(glm::cross((worldVertices[6] - worldVertices[4]), (worldVertices[3] - worldVertices[4])));

	}
	else
	{
		//"min" normals (3)
		faceNormals[0] = glm::cross((worldVertices[2] - worldVertices[0]), (worldVertices[1] - worldVertices[0]));
		faceNormals[1] = glm::cross((worldVertices[1] - worldVertices[0]), (worldVertices[5] - worldVertices[0]));
		faceNormals[2] = glm::cross((worldVertices[5] - worldVertices[0]), (worldVertices[2] - worldVertices[0]));

		//"max" normals (3)
		faceNormals[3] = glm::cross((worldVertices[2] - worldVertices[4]), (worldVertices[7] - worldVertices[4]));
		faceNormals[4] = glm::cross((worldVertices[7] - worldVertices[4]), (worldVertices[5] - worldVertices[4]));
		faceNormals[5] = glm::cross((worldVertices[6] - worldVertices[4]), (worldVertices[3] - worldVertices[4]));
	}
	


	//Normalise all dem normals
	for (int i = 0; i < faceNormals.size(); i++)
	{
		faceNormals[i] = glm::normalize(faceNormals[i]);
	}

	
}

void OBB::setRotation(float degrees, glm::vec3 roatationAxis)
{
	glm::mat4 Identity(1.0);
	glm::mat4 stack = Identity;

	rotation = glm::rotate(stack, float(degrees * DEG_TO_RADIAN), roatationAxis);

	rotatedMin = glm::vec4(objectSpaceMin, 1);
	rotatedMax = glm::vec4(objectSpaceMax, 1);

	rotatedMin = rotatedMin * rotation;
	rotatedMax = rotatedMax * rotation;


	worldSpaceMin = glm::vec3(rotatedMin) + position;
	worldSpaceMax = glm::vec3(rotatedMax) + position;

}



void OBB::printDetails()
{

	std::cout << "Object Space Non Rotated Values: " << std::endl;
	std::cout << "MinX: " << objectSpaceMin.x << std::endl;
	std::cout << "MaxX: " << objectSpaceMax.x << std::endl;
	std::cout << "MinY: " << objectSpaceMin.y << std::endl;
	std::cout << "MaxY: " << objectSpaceMax.y << std::endl;
	std::cout << "MinZ: " << objectSpaceMin.z << std::endl;
	std::cout << "MaxZ: " << objectSpaceMax.z << std::endl;

	std::cout << "Rotated Values for Object Space Min and Max: " << std::endl;
	std::cout << "MinX: " << rotatedMin.x << std::endl;
	std::cout << "MaxX: " << rotatedMax.x << std::endl;
	std::cout << "MinY: " << rotatedMin.y << std::endl;
	std::cout << "MaxY: " << rotatedMax.y << std::endl;
	std::cout << "MinZ: " << rotatedMin.z << std::endl;
	std::cout << "MaxZ: " << rotatedMax.z << std::endl;

	std::cout << "World Space Rotated Values: " << std::endl;
	std::cout << "MinX: " << worldSpaceMin.x << std::endl;
	std::cout << "MaxX: " << worldSpaceMax.x << std::endl;
	std::cout << "MinY: " << worldSpaceMin.y << std::endl;
	std::cout << "MaxY: " << worldSpaceMax.y << std::endl;
	std::cout << "MinZ: " << worldSpaceMin.z << std::endl;
	std::cout << "MaxZ: " << worldSpaceMax.z << std::endl;

}


void OBB::draw()
{
	glm::vec3 boxVerts[8] = { objVertices[0],objVertices[1],objVertices[2],objVertices[3],
							objVertices[4],objVertices[5],objVertices[6],objVertices[7] };
	
	//int mesh = OpenglUtils::createMesh(2, (GLfloat*)boxVerts, nullptr, nullptr, nullptr, NULL, NULL, nullptr);
	//OpenglUtils::drawMesh(mesh, 8, GL_TRIANGLE_FAN);
}
