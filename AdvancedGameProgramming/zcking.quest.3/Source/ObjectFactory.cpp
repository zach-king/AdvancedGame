#include "ObjectFactory.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "SlideBehaviorComponent.h"
#include "CircleBehaviorComponent.h"
#include "PlayerInputComponent.h"
#include "ProjectileComponent.h"
#include "Game.h"
#include "Component.h"
#include "Definitions.h"
#include "Object.h"

#include <memory>

ObjectFactory::ObjectFactory()
{

}

ObjectFactory::~ObjectFactory()
{

}

bool ObjectFactory::Initialize(Game* game)
{
	this->game = game;

	return (game != NULL);
}

std::shared_ptr<Object> ObjectFactory::create(TiXmlElement *pObjectXML)
{
	// Get the creature attributes and create objects
	std::string name = pObjectXML->Attribute("name");

	// Get the correct object factory
	std::shared_ptr<Object> obj = std::make_shared<Object>();

	if (obj == nullptr)
		return false;

	// Set Object name
	obj->setName(name);

	// Initializers struct to be used and reused
	GAME_OBJECTFACTORY_INITIALIZERS inits;
	inits.game = this->game;

	// bool for use with querying
	bool isAnimated;

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
			inits.bodyType = ParseBodyType(pComponentXML->Attribute("type"));
			inits.bodyShape = ParseBodyShape(pComponentXML->Attribute("shape"));
			pComponentXML->QueryFloatAttribute("density", &inits.bodyDensity);
			pComponentXML->QueryFloatAttribute("friction", &inits.bodyFriction);
			pComponentXML->QueryFloatAttribute("restitution", &inits.bodyRestitution);
			pComponentXML->QueryFloatAttribute("angular_damping", &inits.bodyAngDamping);
			pComponentXML->QueryFloatAttribute("linear_damping", &inits.bodyLinDamping);
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
			// Check if the sprite component has multiple sprites (for animation)
			pComponentXML->QueryBoolAttribute("animated", &isAnimated);
			if (isAnimated)
			{
				// Loop through Frame elements
				for (TiXmlElement* frameXML = pComponentXML->FirstChildElement("Frame");
					frameXML != NULL; frameXML = frameXML->NextSiblingElement("Frame"))
				{
					inits.textureIds.push_back(frameXML->Attribute("name"));
				}
			}
			else
			{
				inits.textureIds.push_back(name); // if not animated, just one sprite --> id'ed by obj name
			}
		}

		// Add component
		obj->AddComponent(comp);

		// Get the next component xml element
		pComponentXML = pComponentXML->NextSiblingElement();
	}

	// Initialize the object (and all its components)
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


// Helper method for creating components based off of their component name
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
	else if (compName == "Projectile")
	{
		return std::make_shared<ProjectileComponent>(parent);
	}
	else
	{
		// not "in" library
		return nullptr;
	}
}

GAME_BODY_TYPE ObjectFactory::ParseBodyType(std::string bdType)
{
	if (bdType == "dynamic")
		return GAME_DYNAMIC;
	else if (bdType == "kinematic")
		return GAME_KINEMATIC;
	else if (bdType == "static")
		return GAME_STATIC;

	return GAME_STATIC; // default to static
}

GAME_OBJECT_SHAPE ObjectFactory::ParseBodyShape(std::string bdShape)
{
	if (bdShape == "rectangle")
		return GAME_RECTANGLE;
	else if (bdShape == "circle")
		return GAME_CIRCLE;

	return GAME_CIRCLE; // default to circle
}
