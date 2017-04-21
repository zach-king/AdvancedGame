#pragma once

#include "Component.h"
#include "GraphicsDevice.h"

class TextComponent : public Component
{
public:
	TextComponent();
	TextComponent(std::shared_ptr<Object> owner);
	~TextComponent();

	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS inits);
	void Update();
	bool Finish();

private:
	std::string text;
	GAME_FLT line;
	GraphicsDevice* gDevice;
};