#pragma once

#include "tinyxml\tinyxml.h"
#include "Definitions.h"
#include "Object.h"
#include "Component.h"
#include "Game.h"

#include <memory>
#include <vector>
#include <string>

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();

	bool Initialize(Game*);

	std::shared_ptr<Object> create(TiXmlElement*);	// takes xml element for GameAsset
													// and constructs an object and parses components
													// and initializes it

	// Overloaded version of create, for use at runtime (such as creating Link's arrows)
	std::shared_ptr<Object> create(std::vector<std::string>, GAME_OBJECTFACTORY_INITIALIZERS);

protected:
	// Helper for making components
	std::shared_ptr<Component> CreateComponent(std::string, std::shared_ptr<Object>); 

	// Pointer for one-time storage of game class (for grabbing the libraries and devices)
	Game* game;
};
