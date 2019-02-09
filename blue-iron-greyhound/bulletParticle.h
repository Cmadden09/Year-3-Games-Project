#pragma once
/*============================================================================ =
bulletParticle
Author : Chloe Madden(B00286864) & Adam Stanton.
============================================================================ =*/
#include "Component.h"
#include "glm\common.hpp"
#include <GL/glew.h>
#include "ParticleRenderer.h"
#include <vector>



class bulletParticle : public Component
{
public:
	bulletParticle(glm::vec4 col, int numOfParticles, char* tex, ParticleRenderer* renderer);
	~bulletParticle();

	void init();
	void update(double dt);
	void draw();
	void updateEmitPosition(glm::vec3 pos);

	void emit(glm::vec3 pos, glm::vec3 trajectory, glm::vec3 vel, float dist);


private:



	//VAO & VBO's
	GLuint vao[1];
	GLuint vbo[2];

	char* texture;

	int numOfParticles;
	int nextParticle;

	glm::vec3 emitPosition;

	//glm::vec4 colour;
	std::vector<glm::vec4> colours;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> trajectories;
	std::vector<glm::vec3> velocities;
	std::vector<float> lifeSpan;

	ParticleRenderer* render;
};
