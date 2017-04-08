
#include "Object.h"
#include "Texture.h"
#include "Component.h"

#include <memory>

Object::Object()
{
	initialized = false;
	dead = false;
}

Object::~Object()
{
	// Finish all components upon destruction of their owner
	Finish();
	components.clear();
}

bool Object::Initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	// Initialize all components
	for (auto comp : components)
	{
		if (!comp->Initialize(inits))
			return false;
	}

	initialized = true;
	return true;
}

void Object::AddComponent(std::shared_ptr<Component> component)
{
	// Add a new component to the components vector
	components.push_back(component);
}

void Object::Update()
{
	// Update all components
	for (auto comp : components)
	{
		comp->Update();
	}
}

void Object::Finish()
{
	// Finish all components
	for (auto comp : components)
	{
		comp->Finish();
	}
}

bool Object::isDead()
{
	// Getter for `dead` member
	return dead;
}

void Object::setIsDead(bool isDead)
{
	// Setter for `dead` member
	dead = isDead;
}

void Object::setName(std::string name)
{
	// Setter for `name` member
	this->name = name;
}

std::string Object::getName()
{
	// Getter for `name` member
	return name;
}