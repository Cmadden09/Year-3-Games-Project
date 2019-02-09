#pragma once
/*============================================================================ =
IronRiftsPhysicsSystem
Author : Chloe Madden(B00286864)

This class simply renders Hud Components. All hud Items have an OrthoRenderer
of their own to use and upon update they just send themselves into the renderer
to display on screen.
============================================================================ =*/
class HudComponent;
#include "HudComponent.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<stack>
#include<vector>

#include "System.h"
#include "OpenglUtils.h"
#include "AssimpLoader.h"







//Render HUD items 
class OrthoRenderer : public System
{
public:
	OrthoRenderer(){}
	 
	~OrthoRenderer() {};

	void init();
	void render(HudComponent* item);

private:

	glm::mat4 projection;
	glm::mat4 Identity;

	std::stack<glm::mat4> mvStack;


	GLuint shaderProgram;
	GLuint meshBlock;
	int blockIndexCount;
	


	char* HUDvert
	{
		"	// textured.vert												\n"
		"	// use textures, but no lighting								\n"
		"	#version 330													\n"
		"																	\n"
		"uniform mat4 modelview;											\n"
		"uniform mat4 projection;											\n"
		"																	\n"
		"in  vec3 in_Position;												\n"
		"in vec2 in_TexCoord;												\n"
		"out vec2 ex_TexCoord;												\n"
		"																	\n"
		"	void main(void) {												\n"
		"																	\n"
		"	// vertex into eye coordinates									\n"
		"	vec4 vertexPosition = modelview * vec4(in_Position,1.0);		\n"
		"																	\n"
		"																	\n"
		"	gl_Position =  projection * vertexPosition;						\n"
		"																	\n"
		"	ex_TexCoord = in_TexCoord;										\n"
		"}																	\n"

	};

	char* HUDfrag
	{
		"//HUD Frag													\n"
		"#version 330												\n"
		"															\n"
		"// Some drivers require the following						\n"
		"precision highp float;										\n"
		"															\n"
		"															\n"
		"	uniform sampler2D textureUnit0;							\n"
		"															\n"
		"	in vec2 ex_TexCoord;									\n"
		"															\n"
		"	void main(void) {		\n"
		
		"	vec4 colour =	texture(textureUnit0, ex_TexCoord);		/n"
		
		"	if(	colour.a == 0.2)									\n"
		"		{	discard;	}									\n"
		"															\n"
		"															\n"
		"	// Fragment colour										\n"
		"	out_Color = colour;		\n"
		"															\n"	
		"}															\n"
	};


};
