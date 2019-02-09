#include "MovementComponent.h"
#include <iostream>

MovementComponent::MovementComponent(std::string name)
{
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::init()
{
	moveVector = glm::vec3(0.0f, 0.0f, 0.0f);
}

void MovementComponent::update(double dt)
{
	//Store player position for reuse
	glm::vec3 userPos = this->user->getPosition();

	//Reset the movement vector...
	moveVector = glm::vec3(0.0f, 0.0f, 0.0f);

	//If both of these are active player is moving at an angle and must be slowed down.
	bool verticalMove = false;
	bool horizMove = false;

	//Check for input...
	if (this->input->keyPressed("W"))
	{
		verticalMove = true;
		moveForward(60 * dt);
	}
	if (this->input->keyPressed("S"))
	{
		verticalMove = true;
		moveBackwards(60 * dt);
	}
	if (this->input->keyPressed("A"))
	{
		horizMove = true;
		moveLeft(60 * dt);
	}
	if (this->input->keyPressed("D"))
	{
		horizMove = true;
		moveRight(60 * dt);
	}
	

	//Get current mouseposition
	glm::vec2 mousePosition = this->input->getMousePosition();
	
	//Calculates angle and set player rotation
	//Really just an up vector 
	glm::vec2 playerVec(0,1);

	//Mouse position and an x, y representing the center of the screen (where the player should be)
	//Ideally the values given to set up the game window would be accessible and then no matter the
	//size of screen this would work fine, as of now if we change screen size it will fuck the gameplay up
	glm::vec2 mouseVec = mousePosition - glm::vec2(600,300);		


	float angleInDegrees_ = atan2(mouseVec.y, mouseVec.x) - atan2(playerVec.y, playerVec.x);
	angleInDegrees_ = glm::degrees(angleInDegrees_);


	//Set players rotation based on where the mouse is!
	this->user->setRotationDegrees(angleInDegrees_);



	//Update the user's position by the movement vector... gets squshed if moving at an angle
	if (verticalMove && horizMove)
		this->user->setVelocity( moveVector / glm::vec3(1.5));
	else if(verticalMove | horizMove)
		this->user->setVelocity( moveVector);

}

void MovementComponent::moveForward() { moveForward(0.5f); }
void MovementComponent::moveBackwards() { moveBackwards(0.5f); }
void MovementComponent::moveRight() { moveRight(0.5f); }
void MovementComponent::moveLeft() { moveLeft(0.5f); }
void MovementComponent::moveUp() { moveUp(0.5f); }
void MovementComponent::moveDown(){ moveDown(0.5f); }

void MovementComponent::moveForward(float distance)
{
	//moveVector -= glm::vec3(0.0f + distance*std::sin(this->user->getRotationDegrees()*DEG_TO_RADIAN), 0.0f, 0.0f - (distance)*std::cos(this->user->getRotationDegrees()*DEG_TO_RADIAN));
	moveVector.z -= distance;
}

void MovementComponent::moveBackwards(float distance)
{
	//moveVector += glm::vec3(0.0f + distance*std::sin(this->user->getRotationDegrees()*DEG_TO_RADIAN), 0.0f, 0.0f - distance*std::cos(this->user->getRotationDegrees()*DEG_TO_RADIAN));
	moveVector.z += distance;
}

void MovementComponent::moveRight(float distance)
{
	//moveVector -= glm::vec3(0.0f + distance*std::cos(this->user->getRotationDegrees()*DEG_TO_RADIAN), 0.0f, 0.0f + distance*std::sin(this->user->getRotationDegrees()*DEG_TO_RADIAN));
	moveVector.x += distance;
}

void MovementComponent::moveLeft(float distance)
{
	//moveVector += glm::vec3(0.0f + distance*std::cos(this->user->getRotationDegrees()*DEG_TO_RADIAN), 0.0f, 0.0f + distance*std::sin(this->user->getRotationDegrees()*DEG_TO_RADIAN));
	moveVector.x -= distance;
}

void MovementComponent::moveUp(float distance)
{
	moveVector.y += distance;
}

void MovementComponent::moveDown(float distance)
{
	moveVector.y -= distance;
}

void MovementComponent::setInput(InputSystem * newInput)
{
	this->input = newInput;
}
