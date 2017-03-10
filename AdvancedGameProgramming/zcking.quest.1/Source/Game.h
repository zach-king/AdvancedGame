#pragma once

#include "GameAssetLibrary.h"
#include "ArtAssetLibrary.h"
#include "GraphicsDevice.h"
#include "InputDevice.h"
#include "Timer.h"
#include "Definitions.h"

#include <memory>
#include <vector>

class Game
{
public:
	// Default constructor/destructor
	Game();
	~Game();

	// Initializer; starts devices, timer, etc.
	bool Initialize();

	// Reset the game
	void Reset();

	// Load level from XML file (gamefile, artfile)
	bool LoadLevel(std::string, std::string);

	// Game loop function
	bool Run();

	//  Master update and draw (calls for all objects)
	bool Update();
	void Draw();

private:
	// Libraries and devices
	std::unique_ptr<GameAssetLibrary> gLibrary;
	std::unique_ptr<ArtAssetLibrary> aLibrary;
	std::unique_ptr<GraphicsDevice> gDevice;
	std::unique_ptr<InputDevice> iDevice;
	std::unique_ptr<Timer> timer;

	GAME_FLT gameTime; // maintains overall in-game time
	std::unique_ptr<View> view; // the view 
	std::vector<std::unique_ptr<Object>> objects; // list of all objects in game hierarchy
	void DrawMiniMap(); // draw the mini map
	bool showMiniMap; // flag for showing map or not
};