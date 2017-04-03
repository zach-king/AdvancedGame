#pragma once

#include "GameAssetLibrary.h"
#include "ArtAssetLibrary.h"
#include "GraphicsDevice.h"
#include "InputDevice.h"
#include "Timer.h"
#include "Definitions.h"
#include "Component.h"
#include "Definitions.h"
#include "ObjectFactory.h"

#include <memory>
#include <vector>

class Object;

class Game
{
public:
	Game();
	~Game();
	bool Initialize();
	void Reset();
	bool LoadLevel(std::string, std::string);
	bool Run();
	bool Update();
	void Draw();

private:
	std::unique_ptr<ArtAssetLibrary> aLibrary;
	std::unique_ptr<GraphicsDevice> gDevice;
	std::unique_ptr<InputDevice> iDevice;
	std::unique_ptr<ObjectFactory> oFactory;
	std::unique_ptr<Timer> timer;

	GAME_FLT gameTime; // maintains overall in-game time
	std::unique_ptr<View> view;
	std::vector<std::shared_ptr<Object>> objects;
	void DrawMiniMap();
	bool showMiniMap;
};