#include "GameAssetLibrary.h"
#include "BlueOctorokFactory.h"
#include "BlueLeeverFactory.h"
#include "RedOctorokFactory.h"
#include "RedLeeverFactory.h"

GameAssetLibrary::GameAssetLibrary()
{

}

GameAssetLibrary::~GameAssetLibrary()
{

}

bool GameAssetLibrary::Initialize()
{
	library["Blue Octorok"] = std::make_unique<BlueOctorokFactory>();
	library["Red Octorok"] = std::make_unique<RedOctorokFactory>();
	library["Blue Leever"] = std::make_unique<BlueLeeverFactory>();
	library["Red Leever"] = std::make_unique<RedLeeverFactory>();

	return true;
}

std::unique_ptr<ObjectFactory> GameAssetLibrary::Search(std::string libName)
{
	auto libIter = library.find(libName);
	if (libIter == library.end())
		return nullptr;

	return std::move(libIter->second);
}