#pragma once

#include "Definitions.h"
#include "Object.h"
#include "ObjectFactory.h"
#include "Component.h"
#include "InputDevice.h"
#include "GraphicsDevice.h"
#include "AssetLibrary.h"
#include "GameAssetLibrary.h"
#include "Timer.h"
#include "PhysicsDevice.h"

#include <memory>
#include <vector>

class Game
{
public:
	Game();
	~Game();
	bool Initialize();
	void Reset();
	bool LoadLevel(std::string, std::string, std::string);
	bool Run();
	bool Update();
	void Draw();

	// Getters
	AssetLibrary* getAssetLibrary();
	GraphicsDevice* getGraphicsDevice();
	InputDevice* getInputDevice();
	View* getView();
	ObjectFactory* getObjectFactory();
	Timer* getTimer();
	PhysicsDevice* getPhysicsDevice();

	// Add a new object to the vector of objects for the game
	void AddObject(std::shared_ptr<Object>);

	// Get an object by its string id
	Object* GetObject(std::string);

private:
	// Devices and libraries
	std::unique_ptr<AssetLibrary> aLibrary;
	std::unique_ptr<GraphicsDevice> gDevice;
	std::unique_ptr<InputDevice> iDevice;
	std::unique_ptr<ObjectFactory> oFactory;
	std::unique_ptr<Timer> timer;
	std::unique_ptr<PhysicsDevice> pDevice;

	GAME_FLT gameTime; // maintains overall in-game time
	std::unique_ptr<View> view;
	std::vector<std::shared_ptr<Object>> objects;
	bool showMiniMap;
	bool mapKeyPressed;

	void DrawMiniMap();		// Draws the mini map with SDL
	void KillDeadObjects(); // Kills any objects with the `dead` flag set
	
	// Helper queue for adding new objects at runtime without screwing with iterators
	std::vector<std::shared_ptr<Object>> newObjects;
};