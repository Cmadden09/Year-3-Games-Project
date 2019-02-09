#pragma once
#include "Component.h"
#include "GameObject.h"
#include <iostream>

class InteractiveTestComponent : public Component
{
public:
	InteractiveTestComponent(std::string name);
	~InteractiveTestComponent();

	void init();
	void update(double dt);

	int testingValue;
};