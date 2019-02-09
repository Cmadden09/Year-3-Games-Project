#pragma once
#include "Object.h"

class GameObject;

class Component : public Object
{
public:
	Component() {};
	Component(std::string name);
	virtual ~Component() = 0;

	virtual void init() = 0;
	virtual void update(double dt) = 0;

	void setUser(GameObject *user);
	GameObject *getUser() { return user; }


	void destroy();
	void destroyObj(Object *object);


protected:
	GameObject *user;
};