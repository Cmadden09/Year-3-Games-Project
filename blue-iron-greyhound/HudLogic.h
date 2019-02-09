#pragma once
#include "SDLGLTextureLoader.h"
#include <glm/glm.hpp>

#include "GameObject.h"

class HudLogic 
{
public:
	virtual  void init(GameObject* _user) = 0;
	virtual GLuint textureUpdate() = 0;
	virtual glm::vec3 positionUpdate() = 0;
	virtual glm::vec3 scaleUpdate() = 0;

	bool initialised;
};