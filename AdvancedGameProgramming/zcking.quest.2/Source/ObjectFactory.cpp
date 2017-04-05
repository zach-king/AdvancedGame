#include "ObjectFactory.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "SlideBehaviorComponent.h"
#include "CircleBehaviorComponent.h"
#include "PlayerInputComponent.h"

#include <memory>

ObjectFactory::ObjectFactory()
{

}

ObjectFactory::~ObjectFactory()
{

}

bool ObjectFactory::Initialize(View *view, GraphicsDevice *gDevice, ArtAssetLibrary *aLibrary, InputDevice* iDevice)
{
	this->view = view;
	this->gDevice = gDevice;
	this->aLibrary = aLibrary;
	this->iDevice = iDevice;

	return (view != NULL && gDevice != NULL && aLibrary != NULL && iDevice != NULL);
}

std::shared_ptr<Object> ObjectFactory::create(TiXmlElement *pObjectXML)
{
	// Get the creature attributes and create objects
	std::string name = pObjectXML->Attribute("name");

	// Get the correct object factory
	std::shared_ptr<Object> obj = std::make_shared<Object>();

	if (obj == nullptr)
		return false;

	// Initializers struct to be used and reused
	GAME_OBJECTFACTORY_INITIALIZERS inits;
	inits.view = view;
	inits.gDevice = gDevice;
	inits.iDevice = iDevice;
	inits.aLibrary = aLibrary;
	inits.textureId = name;

	TiXmlElement* pComponentXML = pObjectXML->FirstChildElement("Component");
	while (pComponentXML != NULL)
	{
		// Get component attributes
		std::string compName = pComponentXML->Attribute("name");
		std::shared_ptr<Component> comp = CreateComponent(compName, obj);
		if (comp == nullptr)
			return false; // failed to create component; unknown component

		// Fill in the initializer data from this component's xml
		if (compName == "Body")
		{
			// Query attributes
			pComponentXML->QueryFloatAttribute("x", &inits.position.x);
			pComponentXML->QueryFloatAttribute("y", &inits.position.y);
			pComponentXML->QueryFloatAttribute("angle", &inits.angle);
		}
		else if (compName == "Slide")
		{
			// Query Attributes
			pComponentXML->QueryBoolAttribute("vertical", &inits.verticalSlide);
		}
		else if (compName == "Circle")
		{
			pComponentXML->QueryBoolAttribute("radius", &inits.radius);
		}
		else if (compName == "Sprite")
		{
			inits.texturePath = aLibrary->GetAssetPath(name);
		}

		// Add component
		obj->AddComponent(comp);

		// Get the next component xml element
		pComponentXML = pComponentXML->NextSiblingElement();
	}

	obj->Initialize(inits);

	return obj;
}


/* Overloaded version of create() for use during runtime (such as spawning Link's arrows) */
std::shared_ptr<Object> ObjectFactory::create(std::vector<std::string> compNames, GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	std::shared_ptr<Object> obj = std::make_shared<Object>();

	if (obj == nullptr)
		return nullptr;

	// Loop through component names vector, create and add them to object
	for (std::string compName : compNames)
	{
		std::shared_ptr<Component> comp = CreateComponent(compName, obj);
		if (comp == nullptr)
			return nullptr;

		obj->AddComponent(comp);
	}

	// Initialize the object with the passed-in inits 
	obj->Initialize(inits);
	return obj;
}


std::shared_ptr<Component> ObjectFactory::CreateComponent(std::string compName, std::shared_ptr<Object> parent)
{
	if (compName == "Body")
	{
		return std::make_shared<BodyComponent>(parent);
	}
	else if (compName == "Sprite")
	{
		return std::make_shared<SpriteComponent>(parent);
	}
	else if (compName == "Slide")
	{
		return std::make_shared<SlideBehaviorComponent>(parent);
	}
	else if (compName == "Circle")
	{
		return std::make_shared<CircleBehaviorComponent>(parent);
	}
	else if (compName == "Input")
	{
		return std::make_shared<PlayerInputComponent>(parent);
	}
	else
	{
		// not "in" library
		return nullptr;
	}
}