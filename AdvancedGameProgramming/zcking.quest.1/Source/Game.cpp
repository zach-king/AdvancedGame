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
		std::unique_ptr<Object> obj = gLibrary->Search(name);
		if (obj != nullptr)
		{
			// Create the object
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
	
	// Check if we should toggle the mini map
	if (event == GAME_MAP_TOGGLE)
		showMiniMap = !showMiniMap;

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

	// Draw the mini map if it is toggled
	if (showMiniMap)
	{
		DrawMiniMap();
	}

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

void Game::DrawMiniMap()
{
	// Draw the rectangle for the mini map
	SDL_Renderer* renderer = gDevice->getRenderer();

	SDL_Rect mapRect = {
		SCREEN_WIDTH - MINI_MAP_WIDTH - MINI_MAP_OFFSET,
		MINI_MAP_OFFSET,
		MINI_MAP_WIDTH,
		MINI_MAP_HEIGHT
	};

	// Want half-transparent map so set blend mode beforehand;
	// otherwise the alpha value does nothing
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 230, 200, 165, 100);
	SDL_RenderFillRect(renderer, &mapRect);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
	SDL_RenderDrawRect(renderer, &mapRect);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// Iterate over objects/creatures and draw them on the mini map
	GAME_VEC viewPos = view->getPosition();
	GAME_VEC objPos;
	GAME_INT xOffset = (int)(SCREEN_WIDTH / MINI_MAP_WIDTH);
	GAME_INT yOffset = (int)(SCREEN_HEIGHT / MINI_MAP_HEIGHT);
	GAME_INT xPos, yPos;

	for (auto objIter = objects.begin(); objIter != objects.end(); ++objIter)
	{
		// Get the creature's world map position
		objPos = objIter->get()->getPosition();

		xPos = (int)((objPos.x - viewPos.x) / xOffset) + (SCREEN_WIDTH - MINI_MAP_WIDTH - MINI_MAP_OFFSET);
		yPos = (int)((objPos.y + viewPos.y) / yOffset) + MINI_MAP_OFFSET;

		if (xPos <= (SCREEN_WIDTH - MINI_MAP_WIDTH - MINI_MAP_OFFSET) || xPos >= SCREEN_WIDTH - MINI_MAP_OFFSET ||
			yPos <= MINI_MAP_OFFSET || yPos >= (MINI_MAP_OFFSET + MINI_MAP_HEIGHT))
			continue;

		// Draw a point for that position, but scaled for the mini map	
		SDL_RenderDrawPoint(
			renderer,
			xPos,
			yPos
		);
	}
}