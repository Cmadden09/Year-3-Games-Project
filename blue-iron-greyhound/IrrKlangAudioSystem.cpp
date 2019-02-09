#include "IrrKlangAudioSystem.h"
#include <iostream>
void IrrKlangAudioSystem::init()
{
	//Initialise the audio engine:
	audioEngine = irrklang::createIrrKlangDevice(irrklang::ESOD_AUTO_DETECT, irrklang::ESEO_DEFAULT_OPTIONS, 0);

	if (!audioEngine) //If the engine failed to startup:
	{
		printf("ERROR: IrrKlang Audio Engine failed to start up\n");
	}
}

void IrrKlangAudioSystem::playAudio(char * filePath)
{
	audioStream = audioEngine->play2D(filePath, false, false, true); //Plays the audio file once.

	if (audioStream)
	{
		audioStream->drop(); // release the pointer once it is no longer needed.
		audioStream = 0;
	}
}

void IrrKlangAudioSystem::playAudio(char * filePath, bool looped)
{
	audioStream = audioEngine->play2D(filePath, looped, false, true);

	if (audioStream)
	{
		audioStream->drop(); // release the pointer once it is no longer needed.
		audioStream = 0;
	}

}

void IrrKlangAudioSystem::playAudio(char * filePath, glm::vec3 emmiterPos, glm::vec3 listenerPos)
{
	float distance = sqrt(	((emmiterPos.x - listenerPos.x)*(emmiterPos.x - listenerPos.x)) +
							((emmiterPos.y - listenerPos.y)*(emmiterPos.y - listenerPos.y)) +
							((emmiterPos.z - listenerPos.z)*(emmiterPos.z - listenerPos.z))	);

	if (distance <= 50.0f) 
	{
		float linearVolume = ((50.0f - distance) / 50);
		//linearVolume = 1.0f;
	
		audioStream = audioEngine->play2D(filePath, false, false, true); //Plays the audio file once.

		if (audioStream)
		{
			audioStream->setVolume(linearVolume);
			audioStream->drop(); // release the pointer once it is no longer needed.
			audioStream = 0;
		}
	}
}

void IrrKlangAudioSystem::playAudio(char * filePath, bool looped, glm::vec3 emmiterPos, glm::vec3 listenerPos)
{
	float distance = sqrt(	((emmiterPos.x - listenerPos.x)*(emmiterPos.x - listenerPos.x)) +
							((emmiterPos.y - listenerPos.y)*(emmiterPos.y - listenerPos.y)) +
							((emmiterPos.z - listenerPos.z)*(emmiterPos.z - listenerPos.z))	);

	if (distance <= 100.0f)
	{
		float linearVolume = ((100.0f - distance) / 100);

		audioStream = audioEngine->play2D(filePath, looped, false, true); //Plays the audio file once.

		if (audioStream)
		{
			audioStream->setVolume(linearVolume);
			audioStream->drop(); // release the pointer once it is no longer needed.
			audioStream = 0;
		}
	}
}

void IrrKlangAudioSystem::stopAudio()
{
	audioEngine->removeAllSoundSources();
}

void IrrKlangAudioSystem::stopAudio(char * filePath)
{
	audioEngine->removeSoundSource(filePath);
}
