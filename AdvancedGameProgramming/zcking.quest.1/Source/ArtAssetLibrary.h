#pragma once

#include "GraphicsDevice.h"
#include "Texture.h"

#include <map>
#include <memory>


class ArtAssetLibrary
{
public:
	// Default constructor/destructor
	ArtAssetLibrary();
	~ArtAssetLibrary();

	// Add an asset (texture) to library
	bool AddAsset(std::string, std::string);

	// Initialize the library (set members)
	bool Initialize(GraphicsDevice*);

	// Search for asset and return pointer to its Texture
	std::shared_ptr<Texture> Search(std::string);

	// Helper method for getting the file path to asset's texture
	std::string GetAssetPath(std::string assetName);

private:
	// Map storage (name of asset : texture for asset)
	std::map<std::string, std::shared_ptr<Texture>> library;

	// The graphics device to use for the texture
	GraphicsDevice* gDevice;
};
