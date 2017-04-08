#pragma once

#include "GraphicsDevice.h"
#include "Texture.h"

#include <map>
#include <memory>

class ArtAssetLibrary
{
public:
	ArtAssetLibrary();
	~ArtAssetLibrary();

	// Add texture with textureId and texture path
	bool AddAsset(std::string, std::string);
	bool Initialize(GraphicsDevice*);

	// Find and return texture from its textureId
	std::shared_ptr<Texture> Search(std::string);

	// Helper for getting the path from a texture from textureId
	std::string GetAssetPath(std::string assetName);

private:
	std::map<std::string, std::shared_ptr<Texture>> library;	// Map textureIds to Texture
	GraphicsDevice* gDevice;									// Graphics Device used for loading textures
};
