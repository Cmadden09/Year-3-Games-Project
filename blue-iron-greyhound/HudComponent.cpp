#include "HudComponent.h"
#include "GameObject.h"
#include "PlayerMechanicsComponent.h"

OrthoRenderer renderer;

HudComponent::HudComponent(glm::vec3 pos, glm::vec3 _scale, HudLogic* _logic)
{
	position = pos;
	scale = _scale;

	renderer.init();

	logic = _logic;
}

void HudComponent::update(double dt)
{
	//Initialise the logic class when we have a user reference (This is bad because now it'll be checking this every frame for no reason)
	if(!logic->initialised && this->getUser() != NULL)
		logic->init(this->getUser());

	//Get the logic to update the HUD components data
	texture = logic->textureUpdate();
	///position = logic->positionUpdate();
	///scale = logic->scaleUpdate();
	
	//Render it
	renderer.render(this);
}