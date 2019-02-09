#include "BackgroundMusicComponent.h"

BackgroundMusicComponent::BackgroundMusicComponent(std::string name)
{
}

void BackgroundMusicComponent::init()
{
	audio->playAudio(this->audioPath, true);
}

void BackgroundMusicComponent::update(double dt)
{

}
