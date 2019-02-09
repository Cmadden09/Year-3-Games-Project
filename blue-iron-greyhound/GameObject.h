#pragma once
#include <vector>
#include "Object.h"
#include "Component.h"
#include <glm/glm.hpp>
#include <GL/glew.h>

class GameObject : public Object
{
public:
	GameObject(std::string name);
	virtual ~GameObject();
	void init();
	void update(double dt);

	template<class genericComponent>
	genericComponent *getComponent();
	void addComponent(Component* component);

	void destroy();
	void destroyObj(Object *object);

	//Used to keep track of all other objects in the game...
	//static std::vector<GameObject*> gameObjects;
	//static GameObject *find(std::string name);
	//static void cleanUpObjects();

	void setPosition(glm::vec3 iposition);
	glm::vec3 getPosition() { return position; }

	void setVelocity(glm::vec3 ivel) { velocity = ivel; }
	glm::vec3 getVelocity() { return velocity; }

	void setRotationAxis(glm::vec3 rot) { rotationAxis = rot; }	
	glm::vec3 getRotationAxis() { return rotationAxis; }				
															
	void setRotationDegrees(float deg) { rotationDegrees = deg; }		
	float getRotationDegrees() { return rotationDegrees; }			

	void setScaling(glm::vec3 scale) { scaling = scale; }	
	glm::vec3 getScaling() { return scaling; }

	bool isAlive;

protected:
	std::vector<Component *> componentList;

private:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 scaling;
	glm::vec3 rotationAxis;			
	float rotationDegrees;

	float deacceleration;
	
};

template<class genericComponent>
genericComponent *GameObject::getComponent()
{
	//Initialize the return value as a nullptr in case no component is found.
	genericComponent *component = nullptr;

	//Loop through the component list, if a component of a matching type is found, break and return the component...
	for (int i = componentList.size() - 1; i >= 0; i--)
	{
		if (component = dynamic_cast<genericComponent*>(componentList[i]))
		{
			return component;
		}	
	}
	//If no component found by the end of the loop, will return a nullptr.
	return component;
}
