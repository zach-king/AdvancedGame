#include "SpriteComponent.h"
#include "GameFunctions.h"
#include "GraphicsDevice.h"
#include "Game.h"
#include "BodyComponent.h"
#include "PhysicsDevice.h"

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
		std::shared_ptr<Texture> tex = initializers.game->getAssetLibrary()->SearchTexture(textId);
		if (tex == nullptr)
			return false;

		textures[textId] = tex;

		// Set current texture 
		currentTexture = tex;
		currentTextureId = textId;
	}

	pDevice = initializers.game->getPhysicsDevice();

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

void SpriteComponent::Update()
{
}

bool SpriteComponent::Finish()
{
	this->gDevice = NULL;
	return true;
}

void SpriteComponent::Draw()
{
	//Extract position and angle
	GAME_VEC position = pDevice->GetPosition(_owner.get());
	GAME_FLT angle = pDevice->GetAngle(_owner.get());

	//Render to the Screen
	currentTexture->Draw(gDevice->getRenderer(), position, angle, NULL);
}

Texture * SpriteComponent::getTexture()
{
	return currentTexture.get();
}

std::string SpriteComponent::getTextureId()
{
	return currentTextureId;
}
