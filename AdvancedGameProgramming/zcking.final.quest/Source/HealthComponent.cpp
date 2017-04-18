#include "HealthComponent.h"
#include "Object.h"

HealthComponent::HealthComponent() : Component()
{
}

HealthComponent::HealthComponent(std::shared_ptr<Object> owner) : Component(owner)
{
}

HealthComponent::~HealthComponent()
{
}

bool HealthComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	maxHealth = initializers.health;
	currentHealth = maxHealth;
	aDevice = initializers.game->getAudioDevice();
	game = initializers.game;
	return true;
}

void HealthComponent::Update()
{
	// Check if dead and react
	if (this->IsDead())
	{
		this->_owner->setIsDead(true);

		// Also check if player and if so, play the death sound and show game over text
		if (_owner->getName() == "Player")
		{
			aDevice->setBackgroundMusic("Death");
			game->setGameOver(true);
		}
		else if (_owner->getName() == "Red Pirate")
		{
			// Add score to game
			game->AddScore(RED_PIRATE_SCORE);
		}
		else if (_owner->getName() == "Black Pirate")
		{
			game->AddScore(BLACK_PIRATE_SCORE);
		}
	}
}

bool HealthComponent::Finish()
{
	return true;
}

bool HealthComponent::IsDead()
{
	return currentHealth <= 0;
}

void HealthComponent::TakeDamage(int damage)
{
	currentHealth -= damage;
	if (currentHealth < 0)
		currentHealth = 0;
}

void HealthComponent::AddHealth(int hp)
{
	currentHealth = (currentHealth + hp) % maxHealth;
}

int HealthComponent::GetCurrentHealth()
{
	return currentHealth;
}

int HealthComponent::GetMaxHealth()
{
	return maxHealth;
}