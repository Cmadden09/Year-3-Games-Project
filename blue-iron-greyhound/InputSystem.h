/*=============================================================================
* InputSystem.h
* Author: Adam Stanton
* Abstract parent for input handling systems...
=============================================================================*/

#pragma once
#include "System.h"
#include <string>
#include <glm/glm.hpp>

class InputSystem : public System
{
public:
	InputSystem() {};
	virtual ~InputSystem() {};

	virtual void init() = 0;
	virtual bool keyPressed(std::string key) = 0;
	virtual bool mousePressLeft()=0;
	virtual bool mousePressRight()= 0;
	virtual glm::vec2 getMousePosition() = 0;
	//Need a mouse function!!!!
};