#include "InteractiveTestComponent.h"

InteractiveTestComponent::InteractiveTestComponent(std::string name)
{
	InteractiveTestComponent::name = name;
	testingValue = 0;
}

InteractiveTestComponent::~InteractiveTestComponent()
{
}

void InteractiveTestComponent::init()
{
	std::cout << "Component " << getName() << " belonging to GameObject " << getUser()->getName() << " is now initialized." << std::endl;
}

void InteractiveTestComponent::update(double dt)
{
	testingValue++;
}
