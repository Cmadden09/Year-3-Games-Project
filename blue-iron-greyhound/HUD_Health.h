#pragma once
#include "HudLogic.h"
#include <vector>
#include "MechanicsComponent.h"

class HUD_Health  : public HudLogic
{
public:
	 HUD_Health();

	 //Store a reference to the relevant GameObject and it's mechanics
	 //component which has a lot of the information HUD elements need
	 void init(GameObject* _user);
	
	 //Function with logic to update the HUD visuals
	 GLuint textureUpdate();
	 glm::vec3 positionUpdate();
	 glm::vec3 scaleUpdate();


private:
	std::vector<GLuint>textures;

	GLuint activeTexture;

	GameObject* user;
	MechanicsComponent* playerMech;

	

};