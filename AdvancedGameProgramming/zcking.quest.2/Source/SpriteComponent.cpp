#include "SpriteComponent.h"
#include "BodyComponent.h"
#include "GameFunctions.h"
#include "GraphicsDevice.h"
#include "Texture.h"
#include "ArtAssetLibrary.h"
#include "Game.h"

#include <memory>
#include <map>

SpriteComponent::SpriteComponent() : Component() {}

SpriteComponent::SpriteComponent(std::shared_ptr<Object> owner) : Component(owner)
{
	currentTexture = NULL;
	gDevice = NULL;
	textures = std::map<std::string, std::shared_ptr<Texture>>();
}

SpriteComponent::~SpriteComponent() {}


bool SpriteComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	this->gDevice = initializers.game->getGraphicsDevice();

	//Add Sprite to gDevice
	gDevice->AddSprite(this);

	// Get the Art Asset from the library
	std::vector<std::string> textureIds = initializers.textureIds;
	for (std::string textId : textureIds)
	{
		// Add to textures map
		std::shared_ptr<Texture> tex = initializers.game->getArtAssetLibrary()->Search(textId);
		if (tex == nullptr)
			return false;

		textures[textId] = tex;

		// Set current texture (last tex in loop will be kept as current)
		currentTexture = tex;
		currentTextureId = textId;
	}

	view = initializers.game->getView();

	body = _owner->GetComponent<BodyComponent>();

	return true;
}

bool SpriteComponent::SetTexture(std::string texId)
{
	// Check if the texture is stored in this component
	if (textures.find(texId) == textures.end())
		return false;

	// Set the current texture 
	currentTexture = textures[texId];
	currentTextureId = texId;
	return true;
}

std::unique_ptr<Object> SpriteComponent::Update()
{
	return nullptr;
}

bool SpriteComponent::Finish()
{
	return false;
}

void SpriteComponent::Draw()
{
	//Extract position and angle
	GAME_VEC position = body->getPosition();
	GAME_FLT angle = body->getAngle();

	//Render to the Screen
	currentTexture->Draw(gDevice->getRenderer(), view, position, angle, NULL);
}

Texture * SpriteComponent::getTexture()
{
	return currentTexture.get();
}

std::string SpriteComponent::getTextureId()
{
	return currentTextureId;
}
