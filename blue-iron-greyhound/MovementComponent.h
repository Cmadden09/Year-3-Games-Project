/*=============================================================================
* MovementComponent.h
* Author: Adam Stanton
* Used to update GameObject position (and rotation) values...
=============================================================================*/

#pragma once
#include "Component.h"
#include "GameObject.h"
#include "InputSystem.h"

#define DEG_TO_RADIAN 0.017453293

class MovementComponent : public Component
{
public:
	MovementComponent(std::string name);
	~MovementComponent();

	void init();
	void update(double dt);

	void moveForward();
	void moveBackwards();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();

	void moveForward(float distance);
	void moveBackwards(float distance);
	void moveRight(float distance);
	void moveLeft(float distance);
	void moveUp(float distance);
	void moveDown(float distance);

	void setInput(InputSystem *newInput);
private:
	glm::vec3 moveVector; //The value which we update the game object's position by each update.
	float rotationUpdate; //Probably temp!!!

	InputSystem *input;
};
