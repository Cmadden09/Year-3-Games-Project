/*=============================================================================
* IrrKlangAudioSystem.h
* Author: Adam Stanton
* Concrete auio system using the irrklang audio library, can be used to play 2d or (linear)3d sound...
=============================================================================*/

#pragma once
#include "AudioSystem.h"
#include "irrKlang.h"
#include "glm\glm.hpp"

class IrrKlangAudioSystem : public AudioSystem
{
public:

	IrrKlangAudioSystem(std::string name) {};
	virtual ~IrrKlangAudioSystem() {audioEngine->drop(); }; //deletes the audioEngine.

	void init();

	//.wav or .ogg only...
	//2D Sound...
	void playAudio(char * filePath);
	void playAudio(char * filePath, bool looped); 
	//3D Sound...
	void playAudio(char * filePath, glm::vec3 emmiterPos, glm::vec3 listenerPos);
	void playAudio(char * filePath, bool looped, glm::vec3 emmiterPos, glm::vec3 listenerPos);

	void stopAudio();
	void stopAudio(char * filePath);

protected:
	irrklang::ISound* audioStream;			//stores the sound that is being played.
	irrklang::ISoundEngine* audioEngine;	//Responsible for all irrklang sound processes.
};