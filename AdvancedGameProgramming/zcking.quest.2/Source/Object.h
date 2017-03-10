#pragma once

#include<memory>
#include<iostream>
#include<vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include <Box2D\Box2D.h>

class Component;
class GraphicsDevice;

class GameObject : public std::enable_shared_from_this<GameObject>
{

public:
	GameObject();
	~GameObject();

	bool Initialize(GraphicsDevice* gDevice, std::string, b2World* world, float);
	void AddComponent(std::shared_ptr<Component> component);

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