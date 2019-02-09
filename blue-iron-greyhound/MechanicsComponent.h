#pragma once
#include "Component.h"
#include "AudioSystem.h"
#include "PhysicsSystem.h"
#include "bulletParticle.h"
//timer
#include <ctime>
#include <cstdlib>
#include "time.h"

#define DEG_TO_RADIAN 0.017453293

class MechanicsComponent : public Component
{
public:
	MechanicsComponent() {};
	MechanicsComponent(std::string name) {};
	~MechanicsComponent() {};

	virtual void init() = 0;
	virtual void update(double dt) = 0;

	void setHealth(float health) { this->health = health; }
	void setDamage(float damage) { this->damage = damage; }
	void setWeaponRange(float weaponRange) { this->weaponRange = weaponRange; }
	void setRateOfFire(float rateOfFire) { this->rateOfFire = rateOfFire; }

	void setSpawnPos(glm::vec3 spawnPos) { this->spawnPos = spawnPos; }
	void setAwaitingRespawn(bool awaitingRespawn) { this->awaitingRespawn = awaitingRespawn; }

	void setAudio(AudioSystem *audio) { this->audio = audio; }
	void setPhysics(PhysicsSystem *physics) { this->physics = physics; }
	void setParticleRenderer(bulletParticle *particleRenderer) { this->particleRenderer = particleRenderer; }

	float getHealth() { return this->health; }
	float getDamage() { return this->damage; }
	float getWeaponRange() { return this->weaponRange; }
	float getRateOfFire() { return this->rateOfFire; }

	glm::vec3 getSpawnPos() { return this->spawnPos; }
	bool getAwaitingRespawn() { return this->awaitingRespawn; }

	AudioSystem *getAudio() { return this->audio; }
	PhysicsSystem *getPhysics() { return this->physics; }
	bulletParticle *getParticleRenderer() { return this->particleRenderer; }

	int score;

protected:
	float health, damage, weaponRange, rateOfFire;
	glm::vec3 spawnPos;
	bool awaitingRespawn;

	AudioSystem *audio;
	PhysicsSystem *physics;
	bulletParticle *particleRenderer;

	std::clock_t start;
};
