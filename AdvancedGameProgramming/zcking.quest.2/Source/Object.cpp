
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
	for(auto comp: components)
	{
		comp->Finish();
	}
	components.clear();
}

bool Object::Initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
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
	components.push_back(component);
}

void Object::Update()
{
	for (auto comp : components)
	{
		comp->Update();
	}
}

void Object::Finish()
{
	for (auto comp : components)
	{
		comp->Finish();
	}
}

bool Object::isDead()
{
	return dead;
}

void Object::setIsDead(bool isDead)
{
	dead = isDead;
}

void Object::setName(std::string name)
{
	this->name = name;
}

std::string Object::getName()
{
	return name;
}