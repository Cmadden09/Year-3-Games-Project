#include "TestComponent.h"
#include "InteractiveTestComponent.h"

TestComponent::TestComponent(std::string name)
{
	TestComponent::name = name;
}

TestComponent::~TestComponent()
{
}

void TestComponent::init()
{
	std::cout << "Component " << getName() << " belonging to GameObject " << getUser()->getName() << " is now initialized." << std::endl;
}

void TestComponent::update(double dt)
{
	if (user->getComponent<InteractiveTestComponent>() != nullptr) 
	{
		std::cout << "Taking value from component: " << user->getComponent<InteractiveTestComponent>()->getName() << ": " << user->getComponent<InteractiveTestComponent>()->testingValue << std::endl;
	}
	else {
		std::cout << "No interactive component found!" << std::endl;
	}
	
}
