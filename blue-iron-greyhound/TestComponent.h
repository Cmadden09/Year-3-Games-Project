#pragma once
#include "Component.h"
#include "GameObject.h"
#include <iostream>

class TestComponent : public Component
{
public:
	TestComponent(std::string name);
	~TestComponent();

	void init();
	void update(double dt);
};