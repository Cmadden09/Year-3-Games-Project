#pragma once
/*============================================================================ =
RayCastTestComponent
Author : Chloe Madden(B00286864)
============================================================================ =*/

#include "Component.h"
#include "GameObject.h"
#include "InputSystem.h"
#include "IronRiftsPhysicsSystem.h"
#include "bulletParticle.h"

//timer
#include <ctime>
#include <cstdlib>
#include "time.h"
#define CLOCKS_PER_SEC  ((clock_t)1000)

#define DEG_TO_RADIAN 0.017453293

class RayCastTestComponent : public Component
{
public:
	RayCastTestComponent(std::string name);
	~RayCastTestComponent();

	void init();
	void update(double dt);

	void setRenderer(bulletParticle* renderer);
	void setInput(InputSystem *newInput);
	void setPhysics(PhysicsSystem *newPhysics);
private:
	InputSystem *input;
	PhysicsSystem *physics;
	bulletParticle* bulletRender;

	float rayMagnitude;

	std::clock_t start;
	double deltaTime;
	float fireCoolOffTime;		//number of seconds between bullet fire
	float bulletVelocity;
};
