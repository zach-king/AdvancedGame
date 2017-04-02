#pragma once

#include "Definitions.h"

#include<memory>
#include<vector>

class Component;

class Object
{
public:
	Object();
	~Object();

	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS);
	void AddComponent(std::shared_ptr<Component>);

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

protected:

	std::vector<std::shared_ptr<Component>> components;
	bool initialized;

};