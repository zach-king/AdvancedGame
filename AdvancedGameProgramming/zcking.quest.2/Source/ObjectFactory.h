#pragma once

#include "Object.h"
#include "tinyxml\tinyxml.h"
#include "Component.h"
#include "GraphicsDevice.h"
#include "InputDevice.h"
#include "ArtAssetLibrary.h"
#include "View.h"
#include "Definitions.h"

#include <memory>
#include <vector>
#include <string>

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();

	bool Initialize(View*, GraphicsDevice*, ArtAssetLibrary*, InputDevice*);

	std::shared_ptr<Object> create(TiXmlElement*); // takes xml element for GameAsset
														   // and constructs an object and parses components
														   // and initializes it
	std::shared_ptr<Object> create(std::vector<std::string>, GAME_OBJECTFACTORY_INITIALIZERS);

protected:
	//static std::unique_ptr<ObjectFactory> instance; // singleton class design (used in constructors of children)
	std::shared_ptr<Component> CreateComponent(std::string, std::shared_ptr<Object>); // helper for making components

	// Pointers for initializing components/objects on create()
	View* view;
	GraphicsDevice* gDevice;
	ArtAssetLibrary* aLibrary;
	InputDevice* iDevice;
};
