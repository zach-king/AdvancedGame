#include <iostream>
#include <math.h>

#include "Texture.h"

Texture::Texture()
{
	width = 0;
	height = 0;
	texture = NULL;
	path = "";
}

Texture::~Texture()
{
	free();
}

bool Texture::load(SDL_Renderer* renderer, std::string path)
{
	this->path = path;
	// Destroy existing texture info
	free();

	// The image that's loaded
	SDL_Surface* surface = NULL;

	// Load the image
	surface = IMG_Load(path.c_str());

	// If the image loaded
	if (surface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n",
			path.c_str(), IMG_GetError());
		return false;
	}

	// Color key image
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));

	// Create an optimized iamge
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL)
	{
		printf("Unable to create texture from iamge %s! SDL_Error: %s\n",
			path.c_str(), SDL_GetError());
		return false;
	}

	// Set the height and width from the texture
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	// Free the loaded image; no longer needed
	SDL_FreeSurface(surface);

	return (texture != NULL);
}

void Texture::Draw(SDL_Renderer * renderer, GAME_VEC position, GAME_FLT angle, SDL_Rect * clip)
{
	// Make the rendering quad
	SDL_Rect renderQuad = { position.x, position.y, width, height };

	// Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	// Render to screen
	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle,
		NULL, SDL_FLIP_NONE);
}

void Texture::free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}

std::string Texture::getPath()
{
	return path;
}
