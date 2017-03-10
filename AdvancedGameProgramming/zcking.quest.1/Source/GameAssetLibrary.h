#ifndef GAMEASSETLIBRARY_H
#define GAMEASSETLIBRARY_H

#include "ObjectFactory.h"
#include "Object.h"
#include "Texture.h"

#include <memory>
#include <map>

class GameAssetLibrary
{
public:
	// Default constructor/destructor	
	GameAssetLibrary();
	~GameAssetLibrary();

	// Initializer; creates factories
	bool Initialize();

	// Search for asset, create it, and return pointer to it
	std::unique_ptr<Object> Search(std::string);

private:
	// Map storage (name of asset : pointer to its factory)
	std::map<std::string, std::unique_ptr<ObjectFactory>> library;
};

#endif