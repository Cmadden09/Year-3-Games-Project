#pragma once
/*============================================================================ =
IronRiftsPhysicsSystem
Author : Chloe Madden(B00286864)

This class stores information for position, scaling and logic information for an individual hud
item. HudLogic contains the unique conditions and textures for an indicvidual
HUD item. Eg the HudLogic for health will have loaded and stored id's for all health
textures and will have set conditions which will select the correct texture and make it active.
============================================================================ =*/


class OrthoRenderer;
#include "SDLGLTextureLoader.h"
#include <glm/glm.hpp>
#include<vector>
#include "OrthoRenderer.h"
#include "Component.h"

#include "HudLogic.h"



class HudComponent : public Component
{
public:
	HudComponent(glm::vec3 pos, glm::vec3 scale, HudLogic* _logic);
	~HudComponent(){}

	void update(double dt);

	void init(){}

	GLuint texture;
	glm::vec3 position;
	glm::vec3 scale;

	
	HudLogic * logic;
private:
	
	
};
