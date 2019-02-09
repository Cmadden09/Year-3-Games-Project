/*=============================================================================
* AudioSystem.h
* Author: Adam Stanton
* Abstract parent to any audio system classes...
=============================================================================*/

#pragma once
#include "System.h"
#include "glm\glm.hpp"

class AudioSystem : public System
{
public:

	AudioSystem() {};
	virtual ~AudioSystem() {};

	virtual void init() = 0;

	//2D Sound...
	virtual void playAudio(char * filePath) = 0;
	virtual void playAudio(char * filePath, bool looped) = 0;
	//3D Sound...
	virtual void playAudio(char * filePath, glm::vec3 emmiterPos, glm::vec3 listenerPos) = 0;
	virtual void playAudio(char * filePath, bool looped, glm::vec3 emmiterPos, glm::vec3 listenerPos) = 0;

	virtual void stopAudio() = 0;
	virtual void stopAudio(char * filePath) = 0;
};