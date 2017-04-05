#pragma once

#include "Object.h"
#include "tinyxml\tinyxml.h"
#include "Component.h"
#include "Definitions.h"

#include <memory>
#include <vector>
#include <string>

class Game;

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();

	bool Initialize(Game*);

	std::shared_ptr<Object> create(TiXmlElement*); // takes xml element for GameAsset
														   // and constructs an object and parses components
														   // and initializes it
	std::shared_ptr<Object> create(std::vector<std::string>, GAME_OBJECTFACTORY_INITIALIZERS);

protected:
	//static std::unique_ptr<ObjectFactory> instance; // singleton class design (used in constructors of children)
	std::shared_ptr<Component> CreateComponent(std::string, std::shared_ptr<Object>); // helper for making components

	// Pointer for one-time storage of game class (for grabbing the libraries and devices)
	Game* game;
};
