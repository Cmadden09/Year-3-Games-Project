#pragma once
/*============================================================================ =
MD2Mesh
Author : Chloe Madden(B00286864)
============================================================================ =*/
#include "md2model.h"
#include "anorms.h"
#include "OpenglUtils.h"
#include "SDLGLTextureLoader.h"

#include <stack>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Component.h"
#include "GameObject.h"

#include "CameraComponent.h"


#define DEG_TO_RADIAN 0.017453293

class MD2Mesh : public Component
{
public:
	MD2Mesh();

	~MD2Mesh(){}

	void init();
	void update(double dt);

	void draw(double dt);

	Camera* camera;
private:

	GLuint meshID;
	GLuint textureID;

	GLuint md2VertCount;

	md2model model;

	int currentAnim;

	std::stack<glm::mat4> mvStack;
	glm::mat4 projection;

	//Camera* camera;
	


};
