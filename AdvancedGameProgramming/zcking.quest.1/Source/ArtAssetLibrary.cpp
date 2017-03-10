#include "ArtAssetLibrary.h"

ArtAssetLibrary::ArtAssetLibrary()
{

}

ArtAssetLibrary::~ArtAssetLibrary()
{

}

// Initialize library; set graphics device pointer
bool ArtAssetLibrary::Initialize(GraphicsDevice* gDev)
{
	gDevice = gDev;
	return true;
}

// Add a new asset (create texture and load it)
bool ArtAssetLibrary::AddAsset(std::string assetName, std::string path)
{
	std::shared_ptr<Texture> tex(std::make_shared<Texture>());
	if (!tex->load(gDevice->getRenderer(), path))
		return false;

	library[assetName] = tex;
	return true;
}

// Get the asset file path for a given asset name
std::string ArtAssetLibrary::GetAssetPath(std::string assetName)
{
	auto assetIter = library.find(assetName);
	if (assetIter == library.end())
		return "";
	return assetIter->second->getPath();
}

// Search for asset in the library and return pointer to its texture
std::shared_ptr<Texture> ArtAssetLibrary::Search(std::string assetName)
{
	auto asset = library.find(assetName);
	if (asset == library.end())
		return nullptr;

	return asset->second;
}