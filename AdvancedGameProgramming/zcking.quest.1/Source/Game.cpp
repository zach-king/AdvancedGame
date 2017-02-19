#include "GameAssetLibrary.h"
#include "ArtAssetLibrary.h"
#include "GraphicsDevice.h"
#include "InputDevice.h"
#include "Timer.h"
#include "Definitions.h"
#include "Game.h"

#include "tinyxml\tinyxml.h"

#include <memory>
#include <vector>

Game::Game()
{
	gameTime = 0.0f;
}

Game::~Game()
{

}

bool Game::Initialize()
{
	// Initialize the devices
	gDevice = std::make_unique<GraphicsDevice>(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!gDevice->Initialize(false))
	{
		printf("Graphics Device could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	iDevice = std::make_unique<InputDevice>();
	if (!iDevice->Initialize())
	{
		printf("Input Device could not initalize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	// Initialize the timer
	timer = std::make_unique<Timer>();
	if (!timer->Initialize())
	{
		printf("Frame Timer could not initialize! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}

	// Initialize the libraries
	aLibrary = std::make_unique<ArtAssetLibrary>();
	aLibrary->Initialize(gDevice.get());

	gLibrary = std::make_unique<GameAssetLibrary>();
	gLibrary->Initialize();

	// Initialize the view
	view = std::make_unique<View>();
	if (!view->Initialize(iDevice.get(), 0, 0))
	{
		printf("Could not initialize the View object!\n");
		exit(1);
	}

	return true;
}

void Game::Reset()
{
	// Destroy the View object
	view.reset();

	// Destroy all objects
	objects.clear();

	// Resets size to 0?
	view = std::make_unique<View>();
	if (!view->Initialize(iDevice.get(), 0, 0))
	{
		printf("Could not initialize the View object!\n");
		exit(1);
	}
}

bool Game::LoadLevel(std::string gameXmlFile, std::string artXmlFile)
{
	// Create the XML document object and 
	// Check if it loaded without trouble
	TiXmlDocument artXml(artXmlFile.c_str());
	if (!artXml.LoadFile())
	{
		printf("Unable to load art XML file %s! Tiny XML Error: %s\n", artXmlFile.c_str(), artXml.ErrorDesc());
		return false;
	}

	// Root and object xml pointers
	TiXmlElement* pRootXML = NULL;
	TiXmlElement* pObjectXML = NULL;

	// Parse the XML object; get the root XML element
	pRootXML = artXml.FirstChildElement("Objects");

	// If is not in config file, exit with error
	if (pRootXML == NULL)
		return false;

	// Parse the art assets out of XML file
	pObjectXML = pRootXML->FirstChildElement("Creature");
	while (pObjectXML != NULL)
	{
		// Get the creature attributes and add to art asset library
		aLibrary->AddAsset(pObjectXML->Attribute("name"), pObjectXML->Attribute("sprite"));

		// Get the next creature element
		pObjectXML = pObjectXML->NextSiblingElement("Creature");
	}

	//---------------------------------------------------

	// Create the XML document object and 
	// Check if it loaded without trouble
	TiXmlDocument gameXml(gameXmlFile.c_str());
	if (!gameXml.LoadFile())
	{
		printf("Unable to load game XML file %s! Tiny XML Error: %s\n", gameXmlFile.c_str(), gameXml.ErrorDesc());
		return false;
	}

	// Root and object xml pointers
	pRootXML = NULL;
	pObjectXML = NULL;

	// Parse the XML object; get the root XML element
	pRootXML = gameXml.FirstChildElement();

	// If is not in config file, exit with error
	if (pRootXML == NULL)
		return false;

	// Parse the game assets out of XML file
	pObjectXML = pRootXML->FirstChildElement("GameAsset");
	while (pObjectXML != NULL)
	{
		// Get the asset attributes and create objects
		std::string name = pObjectXML->Attribute("name");
		GAME_FLT angle;
		GAME_VEC pos;
		pObjectXML->QueryFloatAttribute("x", &pos.x);
		pObjectXML->QueryFloatAttribute("y", &pos.y);
		pObjectXML->QueryFloatAttribute("angle", &angle);
		
		// Get the correct object factory
		std::unique_ptr<ObjectFactory> factory = gLibrary->Search(name);
		if (factory != nullptr)
		{
			// Create the object
			auto obj = factory->create();
			obj->Initialize(gDevice->getRenderer(), aLibrary->GetAssetPath(name));
			obj->setStartPosition(pos);
			obj->setPosition(pos);
			obj->setAngle(angle);
			objects.push_back(std::move(obj));
		}

		// Get the next game asset element
		pObjectXML = pObjectXML->NextSiblingElement("GameAsset");
	}

	return true;
}

bool Game::Run()
{
	GAME_EVENT event = iDevice->GetEvent();
	if (event == GAME_QUIT)
		return true;

	// Start the frame's time
	timer->start();

	// Clear the viewport for next render
	gDevice->Begin();

	// Update each object
	Update();

	// Update the View
	view->Update(gameTime);

	// Regulate FPS with frame timer
	timer->fpsRegulate();

	// Draw each object
	Draw();

	// Present render state
	gDevice->Present();

	// Update the overall gameTime with this frame's ticks
	if (!timer->isPaused())
	{
		gameTime += timer->getTicks();
		if (gameTime > FLT_MAX)
			gameTime = 0.0f;
	}

	return false;
}

bool Game::Update()
{
	// Calls Update() on all objects
	for (auto objIter = objects.begin(); objIter != objects.end(); ++objIter)
	{
		(*objIter)->Update();
	}

	return true;
}

void Game::Draw()
{
	// Calls Draw() on all objects
	for (auto objIter = objects.begin(); objIter != objects.end(); ++objIter)
	{
		(*objIter)->Draw(view.get());
	}
}