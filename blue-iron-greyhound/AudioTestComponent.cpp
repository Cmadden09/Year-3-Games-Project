#include "AudioTestComponent.h"

AudioTester::AudioTester(std::string name)
{
	this->name = name;
}

void AudioTester::init()
{
}

void AudioTester::update(double dt)
{
	if (this->input->keyPressed("Z"))
		audio->playAudio("../../assets/audio/bell.wav");
	if (this->input->keyPressed("X"))
		audio->playAudio("../../assets/audio/bell.wav", this->user->getPosition(), glm::vec3(5.0f, 0.0f, 140.0f));
	if (this->input->keyPressed("C"))
		audio->playAudio("../../assets/audio/Surreptitious.ogg");
	if (this->input->keyPressed("V"))
		audio->stopAudio("../../assets/audio/Surreptitious.ogg");
}

void AudioTester::setAudio(IrrKlangAudioSystem * newAudio)
{
	audio = newAudio;
}

void AudioTester::setInput(InputSystem * newInput)
{
	input = newInput;
}
