#pragma once
#include "GameObject.h"
#include "Component.h"
#include "IrrKlangAudioSystem.h"


class BackgroundMusicComponent : public Component
{
public:
	BackgroundMusicComponent() {}
	BackgroundMusicComponent(std::string name);
	~BackgroundMusicComponent() {};

	void init();
	void update(double dt);


	void setAudio(IrrKlangAudioSystem *newAudio) { this->audio = newAudio; }
	void setAudioPath(char* newAudioPath) { this->audioPath = newAudioPath; }
private:
	IrrKlangAudioSystem *audio;
	char* audioPath;
};