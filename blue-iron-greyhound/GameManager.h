#pragma once
#include "System.h"
#include "GameObject.h"

class GameManager : public System
{
public:
	
	void init();



	std::vector<GameObject> activeObjects, innactiveObjects;
};