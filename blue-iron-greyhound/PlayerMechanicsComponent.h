#pragma once
#include "MechanicsComponent.h"
#include "InputSystem.h"

class PlayerMechanicsComponent : public MechanicsComponent
{
public:
	PlayerMechanicsComponent(std::string name);
	~PlayerMechanicsComponent();

	void init();
	void update(double dt);

	void fireWeapon(double dt);

	void setInput(InputSystem *input) { this->input = input; }
	InputSystem *getInput() { return this->input; }

private:
	double cooldownTimer;
	InputSystem *input;
};
