#include "TextComponent.h"
#include "Game.h"

TextComponent::TextComponent() : Component() {}

TextComponent::TextComponent(std::shared_ptr<Object> owner) : Component(owner) {}

TextComponent::~TextComponent()
{

}

bool TextComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	line = inits.line;
	text = inits.text;
	gDevice = inits.game->getGraphicsDevice();

	return (gDevice != NULL);
}

void TextComponent::Update()
{
	gDevice->DrawText(text, line);
}

bool TextComponent::Finish()
{
	return true;
}