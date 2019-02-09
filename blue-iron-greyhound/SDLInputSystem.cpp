#include "SDLInputSystem.h"
#include <iostream>

SDLInputSystem::SDLInputSystem()
{
}

SDLInputSystem::~SDLInputSystem()
{
}

void SDLInputSystem::init()
{
	keyMap.insert(keys("A", 4));
	keyMap.insert(keys("B", 5));
	keyMap.insert(keys("C", 6));
	keyMap.insert(keys("D", 7));
	keyMap.insert(keys("E", 8));
	keyMap.insert(keys("F", 9));
	keyMap.insert(keys("G", 10));
	keyMap.insert(keys("H", 11));
	keyMap.insert(keys("I", 12));
	keyMap.insert(keys("J", 13));
	keyMap.insert(keys("K", 14));
	keyMap.insert(keys("L", 15));
	keyMap.insert(keys("M", 16));
	keyMap.insert(keys("N", 17));
	keyMap.insert(keys("O", 18));
	keyMap.insert(keys("P", 19));
	keyMap.insert(keys("Q", 20));
	keyMap.insert(keys("R", 21));
	keyMap.insert(keys("S", 22));
	keyMap.insert(keys("T", 23));
	keyMap.insert(keys("U", 24));
	keyMap.insert(keys("V", 25));
	keyMap.insert(keys("W", 26));
	keyMap.insert(keys("X", 27));
	keyMap.insert(keys("Y", 28));
	keyMap.insert(keys("Z", 29));

	keyMap.insert(keys("1", 30));
	keyMap.insert(keys("2", 31));
	keyMap.insert(keys("3", 32));
	keyMap.insert(keys("4", 33));
	keyMap.insert(keys("5", 34));
	keyMap.insert(keys("6", 35));
	keyMap.insert(keys("7", 36));
	keyMap.insert(keys("8", 37));
	keyMap.insert(keys("9", 38));
	keyMap.insert(keys("0", 39));
}

bool SDLInputSystem::keyPressed(std::string key)
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	if (keys[keyMap[key]])
	{
		return true;
	}	
	return false;
}

bool SDLInputSystem::mousePressLeft() {

	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent))
	{
		if (sdlEvent.button.button == SDL_BUTTON_LEFT)
		{
			cout << "Mouse Left " << endl;
			return true;
		}
		return false;
	}
}

bool SDLInputSystem::mousePressRight() {
	
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent))
	{
		if (sdlEvent.type == SDL_MOUSEMOTION && sdlEvent.button.button == SDL_BUTTON_RIGHT)
		{
			cout << "Mouse Right" << endl;
			return true;
		}
		return false;
	}
}



glm::vec2 SDLInputSystem::getMousePosition() {
	//pressed = false;
	

	int i = 1;
	SDL_Event sdlEvent;
	//while (SDL_PollEvent(&sdlEvent))
	//{
	
		//if (sdlEvent.type == SDL_QUIT)	//If the user quits:
		//	i = 0;			//End the loop.

		//if (sdlEvent.type == SDL_MOUSEMOTION)
		//{
		
			//mousePos.x = sdlEvent.motion.x;
			//mousePos.y = sdlEvent.motion.y;
			
			int x;
			int y;

			SDL_GetMouseState(&x, &y);

			mousePos.x = x;
			mousePos.y = y;

			//cout << "PosX: " << mousePos.x << "," << "PosY: " << mousePos.y << endl;
	   //}
		
	//}
	return mousePos;
}
//glm::vec2 getMouseOrigin(){}
