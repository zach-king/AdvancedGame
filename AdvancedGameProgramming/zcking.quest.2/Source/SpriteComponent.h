#pragma once

#include "Component.h"
#include "View.h"
#include "BodyComponent.h"

#include <memory>

class Texture;

class SpriteComponent : public Component
{
public:
	// Constructors/Destructors
	SpriteComponent();
	SpriteComponent(std::shared_ptr<Object> owner);
	~SpriteComponent();

	// Overridden methods
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers);
	std::unique_ptr<Object> Update();
	bool Finish();

	// Additional method for drawing
	void Draw();
	
	Texture* getTexture();

protected:
	std::shared_ptr<Texture> texture;
	GraphicsDevice *gDevice;
	View *view;

	std::shared_ptr<BodyComponent> body;
};