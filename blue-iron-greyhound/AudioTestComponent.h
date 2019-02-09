#include "GameObject.h"
#include "Component.h"
#include "InputSystem.h"
#include "IrrKlangAudioSystem.h"


class AudioTester : public Component
{
public:
	AudioTester() {}
	AudioTester(std::string name);
	~AudioTester() {};

	void init();
	void update(double dt);


	void setAudio(IrrKlangAudioSystem *newAudio);
	void setInput(InputSystem *newInput);
private:

	IrrKlangAudioSystem *audio;
	InputSystem *input;
};
