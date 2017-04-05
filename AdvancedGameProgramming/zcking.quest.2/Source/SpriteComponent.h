#pragma once

#include "Component.h"
#include "View.h"
#include "BodyComponent.h"

#include <memory>
#include <map>

class Texture;
class GraphicsDevice;
class View;

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

	bool SetTexture(std::string);
	
	Texture* getTexture();
	std::string getTextureId();

protected:
	std::shared_ptr<Texture> currentTexture; // currently used texture
	std::string currentTextureId;
	std::map<std::string, std::shared_ptr<Texture>> textures; // other textures (if animated)
	GraphicsDevice *gDevice;
	View *view;

	std::shared_ptr<BodyComponent> body;
};