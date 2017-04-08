#include "SpriteComponent.h"
#include "GameFunctions.h"
#include "GraphicsDevice.h"
#include "ArtAssetLibrary.h"
#include "Game.h"
#include "BodyComponent.h"

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

		// Set current texture 
		currentTexture = tex;
		currentTextureId = textId;
	}

	view = initializers.game->getView();

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
	this->gDevice = NULL;
	return true;
}

void SpriteComponent::Draw()
{
	//Extract position and angle
	auto body = _owner->GetComponent<BodyComponent>();
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
