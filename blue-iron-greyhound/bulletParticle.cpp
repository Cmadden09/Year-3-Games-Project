/*============================================================================ =
bulletParticle
Author : Chloe Madden(B00286864) & Adam Stanton.
============================================================================ =*/

#include "bulletParticle.h"


bulletParticle::bulletParticle(glm::vec4 col, int numOfParticles, char* tex, ParticleRenderer* renderer)
{

	for (int i = 0; i < numOfParticles; i++)
	{
		positions.push_back(glm::vec3(0));
		trajectories.push_back(glm::vec3(0));
		velocities.push_back(glm::vec3(0));
		colours.push_back(col);
		lifeSpan.push_back(0);
	}
	


	this->numOfParticles = numOfParticles;
	this->render = renderer;
	this->texture = tex;

	this->emitPosition = glm::vec3(0);
	nextParticle = 0;

	
}


bulletParticle::~bulletParticle()
{

}

void bulletParticle::init()
{
	render->initTexture(texture);

	glGenVertexArrays(1, vao);
	glGenBuffers(2, vbo);
	glBindVertexArray(vao[0]); 
						
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); 
	glBufferData(GL_ARRAY_BUFFER, numOfParticles * sizeof(glm::vec3), positions.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);     

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, numOfParticles * sizeof(glm::vec4), colours.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void bulletParticle::emit(glm::vec3 pos, glm::vec3 trajectory, glm::vec3 vel, float dist)
{
		positions[nextParticle] = pos;
		velocities[nextParticle] = trajectory * vel;
		lifeSpan[nextParticle] = dist;


		//Load next bullet
		if (nextParticle == numOfParticles - 1)
			nextParticle = 0;
		else
			nextParticle++;
}

void bulletParticle::update(double dt)
{

	for (int i = 0; i < numOfParticles; i++)
	{
		if (lifeSpan[i] > 0)
		{
			positions[i] = positions[i] + velocities[i];
			lifeSpan[i] -= glm::length(velocities[i]);
		}
	}

	draw();
}

void bulletParticle::updateEmitPosition(glm::vec3 pos)
{
	emitPosition = pos;
}

void bulletParticle::draw()
{
	render->updateShader(positions[0]);


	//Update the positions...
	glBindVertexArray(vao[0]); 
							  
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); 
	glBufferData(GL_ARRAY_BUFFER, numOfParticles * sizeof(glm::vec3), positions.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);     
						
	//Colour doesn't seem to be setting?
	glBindVertexArray(vao[1]); 
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, numOfParticles * sizeof(glm::vec4), colours.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);    



	//pre draw settings
	glEnable(GL_POINT_SPRITE); //use for particles.
	glEnable(GL_PROGRAM_POINT_SIZE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	
	//Draw all of our particles...
	for (int i = 0; i < numOfParticles; i++)
	{
		if (lifeSpan[i] > 0)
		{
			render->updateShader(positions[i]);
			glDrawArrays(GL_POINTS, i, 1);
		}
		
	}
	glBindVertexArray(0);

	////post draw settings
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
}


