#pragma once

#include "Definitions.h"
#include "Component.h"

#include <memory>
#include <vector>
#include <string>

class Object
{
public:
	Object();
	~Object();

	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS);
	void AddComponent(std::shared_ptr<Component>);

	bool isDead();
	void setIsDead(bool);

	template<class T>
	std::shared_ptr<T> GetComponent()
	{
		for (auto comp : components)
		{
			std::shared_ptr<T> target;
			if ((target = std::dynamic_pointer_cast<T>(comp)))
			{
				return(target);
			}
		}

		//Return NULL;
		return(std::shared_ptr<T>());
	}

	void Update();
	void Finish();

	// Give the object a name such as "Player" or "Blue Leever"
	// (useful for looking for a type of game object, while maintaining generics)
	std::string getName();
	void setName(std::string);

protected:
	// Vector of components attached to this object
	std::vector<std::shared_ptr<Component>> components;
	bool initialized; // whether or not initialized yet
	bool dead;		  // whether or not this object is dead (tells game to kill it)
	std::string name; // name identifier

};