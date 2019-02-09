#include "CameraComponent.h"
#include "GameObject.h"

#define DEG_TO_RADIAN 0.017453293

Camera::Camera(std::string name)
{
	this->name = name;
}


void Camera::init()
{


	offset = glm::vec3(0.0, 40.0, 10.0);				//top down offset


	//offset = glm::vec3(0.0, 5.0, 20.0);					//first person offset
}


void Camera::update(double dt)
{
	glm::vec3 playerPos = getUser()->getPosition();
	this->eye = playerPos;
	this->eye += offset;

	if (this->input->keyPressed("Q"))
		this->rotation++;
	if (this->input->keyPressed("E"))
		this->rotation--;

	//Nice top down perspective
	this->at = glm::vec3(playerPos.x + 1.0f*std::sin(rotation*DEG_TO_RADIAN), playerPos.y, playerPos.z - 1.0f*std::cos(rotation*DEG_TO_RADIAN));

	//First person perspective
	//this->at = glm::vec3(eye.x + 1.0f*std::sin(rotation*DEG_TO_RADIAN), eye.y, eye.z - 1.0f*std::cos(rotation*DEG_TO_RADIAN));
	

}

void Camera::setEye(glm::vec3 newEye)
{
	this->eye = newEye;
}

void Camera::setAt(glm::vec3 newAt)
{
	this->at = newAt;
}

void Camera::setUp(glm::vec3 newUp)
{
	this->up = newUp;
}

void Camera::setRotation(float newRotation)
{
	this->rotation = newRotation;
}



glm::vec3 Camera::getEye()
{
	return eye;
}

glm::vec3 Camera::getAt()
{
	return at;
}
glm::vec3 Camera::getUp()
{
	return up;
}
float Camera::getRotation()
{
	return rotation;
}

void Camera::setInput(InputSystem * newInput)
{
	input = newInput;
}
