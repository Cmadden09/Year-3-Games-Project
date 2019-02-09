/*============================================================================ =
MD2Mesh
Author : Chloe Madden(B00286864)
============================================================================ =*/

#include "MD2Mesh.h"

MD2Mesh::MD2Mesh()
{
	currentAnim = 1;
	md2VertCount = 0;
	mvStack.push(glm::mat4(1));
	projection = glm::perspective(float(60.0f*DEG_TO_RADIAN), 1200.0f / 600.0f, 0.5f, 2000.0f);
}


void MD2Mesh::init()
{
	textureID = SDLGLTextureLoader::loadMd2Bitmap("../../assets/MD2/hayden.bmp");
	meshID = model.ReadMD2Model("../../assets/MD2/ROBOT.MD2");
	md2VertCount = model.getVertDataCount();
}


void MD2Mesh::update(double dt)
{
	glm::vec3 eye = camera->getEye();
	glm::vec3 at = camera->getAt();
	glm::vec3 up(0, 1, 0);

	mvStack.top() = glm::lookAt(eye, at, up);


	draw(dt);
}


void MD2Mesh::draw(double dt)
{
	model.Animate(currentAnim, 5 * dt);

	OpenglUtils::updateMesh(meshID, 0, model.getAnimVerts(), model.getVertDataSize());

	GLuint ShaderProgram = 3;

	glm::vec3 pos = this->getUser()->getPosition();

	float r = this->getUser()->getRotationDegrees();

	glm::vec3 scale = this->getUser()->getScaling();

	glm::vec3 rotAxis = this->getUser()->getRotationAxis();




	glDisable(GL_CULL_FACE);


	glUseProgram(ShaderProgram);

	OpenglUtils::setUniformMatrix4fv(ShaderProgram, "projection", glm::value_ptr(projection));

	glBindTexture(GL_TEXTURE_2D, textureID);
	

	mvStack.push(mvStack.top());

	mvStack.top() = glm::translate(mvStack.top(), glm::vec3(pos.x, pos.y - 0.85, pos.z));
	mvStack.top() = glm::rotate(mvStack.top(), float(-90.0f*DEG_TO_RADIAN), glm::vec3(1.0f, 0.0f, 0.0f));//sets character upright
	mvStack.top() = glm::rotate(mvStack.top(), float(r*DEG_TO_RADIAN), glm::vec3(0.0f, 0.0f, 1.0f));
	mvStack.top() = glm::rotate(mvStack.top(), float(r*DEG_TO_RADIAN), rotAxis);

	mvStack.top() = glm::scale(mvStack.top(), scale);//scales character in its 3 dimensions
	OpenglUtils::setUniformMatrix4fv(ShaderProgram, "modelview", glm::value_ptr(mvStack.top()));
	//OpenglUtils::setMaterial(ShaderProgram, material0);
	OpenglUtils::drawMesh(meshID, md2VertCount, GL_TRIANGLES);
	mvStack.pop();



	glEnable(GL_CULL_FACE);
}