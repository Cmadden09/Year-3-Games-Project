#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>
#include "Component.h"
#include "InputSystem.h"


class Camera : public Component
{
public:
	Camera() {}
	Camera(std::string name);
	~Camera() {};

	void init();
	void update(double dt);

	void setEye(glm::vec3 newEye);
	void setAt(glm::vec3 newEye);
	void setUp(glm::vec3 newEye);
	void setRotation(float newRotation);

	glm::vec3 getEye();
	glm::vec3 getAt();
	glm::vec3 getUp();
	float getRotation();

	void setInput(InputSystem *newInput);
private:

	glm::vec3 offset;		//affects the cameras position relevant to player object
	glm::vec3 eye;
	glm::vec3 at;
	glm::vec3 up;
	float rotation;

	InputSystem *input;
};

#endif