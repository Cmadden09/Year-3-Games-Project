#include "OrthoRenderer.h"

#define DEG_TO_RADIAN 0.017453293

void OrthoRenderer::init()
{
	//Load shader
	shaderProgram = OpenglUtils::initShaders(HUDvert, HUDfrag);

	//Load cube mesh which will be used to display HUD textures ons
	vector<int> meshIDs;
	vector<int> indexCounts;
	vector<glm::vec3> minmax;

	AssimpLoader::loadObjectData("../../assets/cube_with_2UVs.DAE", meshIDs, indexCounts, minmax);

	meshBlock = meshIDs[0];
	blockIndexCount = indexCounts[0];

	
	//set up model view matric
	glm::mat4 modelview(1.0);
	mvStack.push(modelview);



	//set projection matrix
	///projection = glm::ortho(0.0f, 1200.0f, 0.0f, 600.0f, 0.1f, 100.0f);
	projection = glm::perspective(float(60.0f*DEG_TO_RADIAN), 1200.0f / 600.0f, 0.5f, 2000.0f);
	

}


void OrthoRenderer::render(HudComponent* item)
{

	//glDepthMask(GL_FALSE);

		glUseProgram(shaderProgram);
		OpenglUtils::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));



		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, item->texture);

	
		mvStack.push(mvStack.top());

		mvStack.top() = glm::translate(mvStack.top(), item->position);
		mvStack.top() = glm::scale(mvStack.top(), item->scale);
		OpenglUtils::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
		OpenglUtils::drawIndexedMesh(meshBlock, blockIndexCount, GL_TRIANGLES);

		mvStack.pop();
	
	//glDepthMask(GL_TRUE);
}