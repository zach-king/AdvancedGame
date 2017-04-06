#pragma once

#include "Object.h"
#include "Component.h"
#include "Texture.h"
#include "View.h"
#include "BodyComponent.h"

#include <memory>
#include <map>

class GraphicsDevice;

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

	// My advanced Sprite Component can have multiple textures for it use (animation)
	// the currentTexture is the texture being used. SetTexture() is used to ask for 
	// a change in texture based off the textureIds (string name)
	bool SetTexture(std::string);

	// Gets the currentTexture
	Texture* getTexture();

	// Gets the currentTexture Id (string name)
	std::string getTextureId();

protected:
	std::shared_ptr<Texture> currentTexture; // currently used texture
	std::string currentTextureId;			 // currently used texture Id
	std::map<std::string, std::shared_ptr<Texture>> textures; // all stored textures (only has one if not animated)
	GraphicsDevice *gDevice;				// Pointer to graphics device for drawing textures
	View *view;								// Need view to pass in for drawing, so use this for one-time store
	std::shared_ptr<BodyComponent> body;	// Body position and angle used for drawing 
};