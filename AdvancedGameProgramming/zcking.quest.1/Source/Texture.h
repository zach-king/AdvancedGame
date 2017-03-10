#pragma once

#include "View.h"
#include "Definitions.h"

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Texture
{
public:
	// Default constructor/destructoe
	Texture();
	~Texture();

	// Load texture from path
	bool load(SDL_Renderer* renderer, std::string path);

	// Draw the texture using data from view and object's position, etc.
	void Draw(SDL_Renderer* renderer, View* view, GAME_VEC position, GAME_FLT angle,
		SDL_Rect* clip = NULL);

	// Deallocate texture
	void free();

	// Get image dimensions
	int getWidth();
	int getHeight();

	std::string getPath();

private:
	// The actual hardware texture
	SDL_Texture* texture;

	// Image dimensions
	int width;
	int height;
	std::string path;
};