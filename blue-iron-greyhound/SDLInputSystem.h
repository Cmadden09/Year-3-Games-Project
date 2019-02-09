/*=============================================================================
* SDLInputSystem.h
* Author: Adam Stanton
* Uses SDL to deal with user input using the keyboard and mouse...
=============================================================================*/

#pragma once
#include "InputSystem.h"
#include <SDL.h>
#include <string>
#include <map>
#include <iostream>

using namespace std;

typedef std::pair<std::string, unsigned int> keys;

class SDLInputSystem : public InputSystem
{
public:
	SDLInputSystem();
	virtual ~SDLInputSystem();

	void init();
	bool keyPressed(std::string);
	bool mousePressLeft();
	bool mousePressRight();
	glm::vec2 getMousePosition();
 
	//glm::vec2 getMouseOrigin();
	

	//Need a mouse function!!!!
private:
	glm::vec2 mousePos;

	std::map<std::string, unsigned int> keyMap;
	bool pressed;
	//glm::vec2 mousePos;
};