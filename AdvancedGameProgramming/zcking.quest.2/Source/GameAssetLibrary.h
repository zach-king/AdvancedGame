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
	GameAssetLibrary();
	~GameAssetLibrary();
	bool Initialize();
	std::unique_ptr<Object> Search(std::string);

private:
	std::map<std::string, std::unique_ptr<ObjectFactory>> library;
};

#endif