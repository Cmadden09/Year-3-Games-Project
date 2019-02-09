#ifndef RenderingSystem_H
#define RenderingSystem_H

#include "System.h"
class MeshComponent;
class Camera;



class RenderingSystem : public System
{
public:
	RenderingSystem() {}
	virtual ~RenderingSystem() {};

	virtual void init() = 0;

	virtual void swapBuffers() = 0;
	virtual void clearScreen() = 0;

	virtual void draw(MeshComponent* mesh) = 0;
	virtual void loadTexture(MeshComponent* meshComponent, char * fileName) = 0;
	virtual void loadObject(MeshComponent* mesh, const char * filename) = 0;

	Camera* camera;
private:

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 lightPosition;


};
#endif