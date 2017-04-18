#pragma once

#include "Component.h"
#include "AudioDevice.h"
#include "Game.h"

class Object;

class HealthComponent : public Component
{
public:
	HealthComponent();
	HealthComponent(std::shared_ptr<Object> owner);
	~HealthComponent();

	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers);
	void Update();
	bool Finish();

	bool IsDead();
	void TakeDamage(int damage);
	void AddHealth(int hp);

	int GetCurrentHealth();
	int GetMaxHealth();

private:
	int currentHealth;
	int maxHealth;
	AudioDevice* aDevice;
	Game* game;
};