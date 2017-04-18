#include "GameAssetLibrary.h"
#include "AssetLibrary.h"
#include "GraphicsDevice.h"
#include "InputDevice.h"
#include "Timer.h"
#include "Definitions.h"
#include "Game.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "PlayerInputComponent.h"
#include "HealthComponent.h"
#include "ObjectFactory.h"

#include "tinyxml\tinyxml.h"

#include <memory>
#include <vector>

Game::Game()
{
	gameTime = 0.0f;
	gameOver = false;
	score = 0;
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

	// Initialize the input device
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

	// Phsyics Device
	GAME_VEC gravity;
	gravity.x = GRAVITY_X;
	gravity.y = GRAVITY_Y;
	pDevice = std::make_unique<PhysicsDevice>(gravity);
	if (!pDevice->Initialize(this))
	{
		printf("Physics Device could not initialize!\n");
		exit(1);
	}

	// Initialize the libraries
	aLibrary = std::make_unique<AssetLibrary>();
	bool loaded = aLibrary->Initialize(gDevice.get());
	if (!loaded)
	{
		printf("Could not initialize the Art Asset Library!\n");
		exit(1);
	}

	// Initialize the Object factory
	oFactory = std::make_unique<ObjectFactory>();
	loaded = oFactory->Initialize(this);
	if (!loaded)
	{
		printf("Could not initialize the Object Factory!\n");
		exit(1);
	}

	// Set the font
	std::string fontPath = "./Assets/Fonts/AstronBoyWonder.ttf";
	font = TTF_OpenFont(fontPath.c_str(), 35);
	if (font == NULL)
	{
		printf("Failed to open font %s. SDL_ttf Error: %s\n", fontPath.c_str(), TTF_GetError());
		return false;
	}

	// Add Physics borders to edge of screen (none on top because enemies move past it and player's InputComponent blocks it anyway)
	pDevice->CreateEdge({ PLAYER_SIDE_PADDING, 0 }, { PLAYER_SIDE_PADDING, SCREEN_HEIGHT - 16 }); // left side
	//pDevice->CreateEdge({ PLAYER_SIDE_PADDING, SCREEN_HEIGHT - 16}, { SCREEN_WIDTH - PLAYER_SIDE_PADDING, SCREEN_HEIGHT - 16}); // bottom
	pDevice->CreateEdge({ SCREEN_WIDTH - 16, SCREEN_HEIGHT - 16 }, { SCREEN_WIDTH - 16, 0 }); // right

	return true;
}

void Game::Reset()
{
	// Destroy all objects
	objects.clear();
}

bool Game::LoadLevel(std::string gameXmlFile, std::string artXmlFile, std::string physicsXmlFile, std::string audioXmlFile)
{
	if (!aLibrary->InitializeLibraries(artXmlFile, physicsXmlFile))
	{
		printf("Unable to initialize the Asset Library from XML File!\n");
		return false;
	}

	// Initialize the Audio Device
	aDevice = std::make_unique<AudioDevice>();
	if (!aDevice->Initialize(audioXmlFile))
	{
		printf("Unable to initialize the Audio Device!\n");
		return false;
	}


	// Create the XML document object and 
	// Check if it loaded without trouble
	TiXmlDocument gameXml(gameXmlFile.c_str());
	if (!gameXml.LoadFile())
	{
		printf("Unable to load game XML file %s! Tiny XML Error: %s\n", gameXmlFile.c_str(), gameXml.ErrorDesc());
		return false;
	}

	// Root and object xml pointers
	TiXmlElement* pRootXML = NULL;
	TiXmlElement* pObjectXML = NULL;
	TiXmlElement* pComponentXML = NULL;

	// Parse the XML object; get the root XML element
	pRootXML = gameXml.FirstChildElement();

	// If is not in config file, exit with error
	if (pRootXML == NULL)
		return false;

	// Parse the game assets out of XML file
	std::string musicClip = pRootXML->Attribute("music"); // the background music to play

	pObjectXML = pRootXML->FirstChildElement("GameAsset");
	while (pObjectXML != NULL)
	{
		// factory create object and pass xml
		std::shared_ptr<Object> obj = oFactory->create(pObjectXML);
		objects.push_back(obj);

		// Get the next game asset element
		pObjectXML = pObjectXML->NextSiblingElement("GameAsset");
	}

	// Start playing the background music
	aDevice->setBackgroundMusic(musicClip);

	return true;
}

bool Game::Run()
{
	if (iDevice->GetEvent(GAME_QUIT))
		return true;


	// Start the frame's time
	timer->start();

	// Clear the viewport for next render
	gDevice->Begin();

	// Update each object
	Update();

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
	// Calls Update() on all objects and input device
	iDevice->Update();

	// Kill any dead objects
	KillDeadObjects();

	// Update all objects
	for (auto objIter = objects.begin(); objIter != objects.end(); ++objIter)
	{
		(*objIter)->Update();
	}

	// Update physics device
	pDevice->Update(1.0f / 10.0f);

	// Add any new objects that were created at runtime
	for (auto objIter = newObjects.begin(); objIter != newObjects.end(); ++objIter)
	{
		objects.push_back((*objIter));
	}
	// And the clear the newObjects list
	newObjects.clear();

	return true;
}

void Game::Draw()
{
	// Draw the UI
	DrawUI();

	// Calls Draw() on all objects
	for (auto objIter = objects.begin(); objIter != objects.end(); ++objIter)
	{
		(*objIter)->GetComponent<SpriteComponent>()->Draw();
	}
}

AssetLibrary * Game::getAssetLibrary()
{
	return aLibrary.get();
}

InputDevice* Game::getInputDevice()
{
	return iDevice.get();
}

GraphicsDevice* Game::getGraphicsDevice()
{
	return gDevice.get();
}

ObjectFactory * Game::getObjectFactory()
{
	return oFactory.get();
}

Timer* Game::getTimer()
{
	return timer.get();
}

PhysicsDevice* Game::getPhysicsDevice()
{
	return pDevice.get();
}

AudioDevice* Game::getAudioDevice()
{
	return aDevice.get();
}

void Game::AddObject(std::shared_ptr<Object> obj)
{
	newObjects.push_back(obj); // push to the vector of new objects to be added before next update
}

Object * Game::GetObject(std::string name)
{
	for (auto obj : objects)
	{
		if (obj->getName() == name)
			return obj.get();
	}

	return NULL;
}

// Kill any objects with the `dead` flag set
void Game::KillDeadObjects()
{
	for (auto objIter = objects.begin(); objIter != objects.end();)
	{
		if ((*objIter)->isDead())
		{
			// Kill the dead object
			(*objIter)->Finish();

			// Remove the object
			objIter = objects.erase(objIter);
		}
		else
		{
			++objIter;
		}
	}
}


void Game::DrawUI()
{
	// Draw the UI
	SDL_Color textColor = { 255, 255, 255, 255 };

	// Show "Game Over" if game is over
	int width = 0, height = 0;
	if (gameOver)
	{
		SDL_Texture* gameOverTex = SDL_CreateTextureFromSurface(gDevice->getRenderer(), TTF_RenderText_Solid(font, "GAME OVER", textColor));

		SDL_QueryTexture(gameOverTex, NULL, NULL, &width, &height);
		SDL_Rect renderQuad = { (SCREEN_WIDTH / 2) - (width / 2), (SCREEN_HEIGHT / 2) - height, width, height };

		SDL_RenderCopy(gDevice->getRenderer(), gameOverTex, NULL, &renderQuad);
	}

	//---------------------------------------------------------------------------------------
	//				HEALTH UI
	//---------------------------------------------------------------------------------------

	// Get the player to retrieve their health
	auto player = getPlayer();
	if (player == nullptr)
	{
		return;
	}
	int health = player->GetComponent<HealthComponent>()->GetCurrentHealth();
	char hpText[50];
	snprintf(hpText, sizeof(hpText), "Health: %d", health);

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gDevice->getRenderer(), TTF_RenderText_Solid(font, hpText, textColor));

	SDL_QueryTexture(textTexture, NULL, NULL, &width, &height);
	SDL_Rect renderQuad = { ((int)SCREEN_WIDTH - width) - (int)UI_HEALTH_PADDING, UI_HEALTH_PADDING, width, height };

	SDL_RenderCopy(gDevice->getRenderer(), textTexture, NULL, &renderQuad);

	//-----------------------------------------------------------------------------------------
	//				SCORE UI
	//-----------------------------------------------------------------------------------------
	char scoreText[50];
	snprintf(scoreText, sizeof(scoreText), "Score: %d", score);

	SDL_Texture* scoreTex = SDL_CreateTextureFromSurface(gDevice->getRenderer(), TTF_RenderText_Solid(font, scoreText, textColor));
	SDL_QueryTexture(scoreTex, NULL, NULL, &width, &height);
	renderQuad = { UI_HEALTH_PADDING, UI_HEALTH_PADDING, width, height };
	SDL_RenderCopy(gDevice->getRenderer(), scoreTex, NULL, &renderQuad);
}


std::shared_ptr<Object> Game::getPlayer()
{
	for (auto obj : objects)
	{
		if (obj->getName() == "Player")
			return obj;
	}

	return nullptr;
}

void Game::setGameOver(bool go)
{
	gameOver = go;
}

void Game::AddScore(GAME_INT sc)
{
	score += sc;
}

GAME_INT Game::GetScore()
{
	return score;
}