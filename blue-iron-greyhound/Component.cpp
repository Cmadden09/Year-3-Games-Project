#include "Component.h"

Component::Component(std::string name)
{
	Component::name = name;
}


Component::~Component()
{
}

void Component::setUser(GameObject * user)
{
	Component::user = user;
}

void Component::destroy()
{
}

void Component::destroyObj(Object * object)
{
}
