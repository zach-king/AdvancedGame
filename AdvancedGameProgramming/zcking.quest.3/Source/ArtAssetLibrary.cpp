#include "ArtAssetLibrary.h"

ArtAssetLibrary::ArtAssetLibrary()
{

}

ArtAssetLibrary::~ArtAssetLibrary()
{

}

bool ArtAssetLibrary::Initialize(GraphicsDevice* gDev)
{
	gDevice = gDev;
	return true;
}

bool ArtAssetLibrary::AddAsset(std::string assetName, std::string path)
{
	// Make new texture and load it from the path given
	std::shared_ptr<Texture> tex(std::make_shared<Texture>());
	if (!tex->load(gDevice->getRenderer(), path))
		return false;

	// Store the new texture in our library
	library[assetName] = tex;
	return true;
}

std::string ArtAssetLibrary::GetAssetPath(std::string assetName)
{
	// Find the path for the given textureId
	auto assetIter = library.find(assetName);
	if (assetIter == library.end())
		return "";

	return assetIter->second->getPath();
}

std::shared_ptr<Texture> ArtAssetLibrary::Search(std::string assetName)
{
	// Find the texture with the given textureId
	auto asset = library.find(assetName);
	if (asset == library.end())
		return nullptr;

	return asset->second;
}