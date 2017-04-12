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
	return true;
}

std::unique_ptr<Object> HealthComponent::Update()
{
	// Check if dead and react
	if (this->IsDead())
	{
		this->_owner->setIsDead(true);
	}

	return nullptr;
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