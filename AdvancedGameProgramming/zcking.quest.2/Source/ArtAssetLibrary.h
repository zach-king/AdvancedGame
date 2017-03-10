#ifndef ARTASSETLIBRARY_H
#define ARTASSETLIBRARY_H

#include "GraphicsDevice.h"
#include "Texture.h"

#include <map>
#include <memory>

class ArtAssetLibrary
{
public:
	ArtAssetLibrary();
	~ArtAssetLibrary();
	bool AddAsset(std::string, std::string);
	bool Initialize(GraphicsDevice*);
	std::shared_ptr<Texture> Search(std::string);
	std::string GetAssetPath(std::string assetName);

private:
	std::map<std::string, std::shared_ptr<Texture>> library;
	GraphicsDevice* gDevice;
};

#endif