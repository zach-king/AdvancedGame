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
	std::shared_ptr<Texture> tex(std::make_shared<Texture>());
	if (!tex->load(gDevice->getRenderer(), path))
		return false;

	library[assetName] = tex;
	return true;
}

std::string ArtAssetLibrary::GetAssetPath(std::string assetName)
{
	auto assetIter = library.find(assetName);
	if (assetIter == library.end())
		return "";
	return assetIter->second->getPath();
}

std::shared_ptr<Texture> ArtAssetLibrary::Search(std::string assetName)
{
	auto asset = library.find(assetName);
	if (asset == library.end())
		return nullptr;

	return asset->second;
}