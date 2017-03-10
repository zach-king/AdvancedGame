#include "GameAssetLibrary.h"
#include "BlueOctorokFactory.h"
#include "BlueLeeverFactory.h"
#include "RedOctorokFactory.h"
#include "RedLeeverFactory.h"

#include <iterator>
#include <map>

GameAssetLibrary::GameAssetLibrary()
{

}

GameAssetLibrary::~GameAssetLibrary()
{

}

// Initialize all the factories
bool GameAssetLibrary::Initialize()
{
	library["Blue Octorok"] = std::make_unique<BlueOctorokFactory>();
	library["Red Octorok"] = std::make_unique<RedOctorokFactory>();
	library["Blue Leever"] = std::make_unique<BlueLeeverFactory>();
	library["Red Leever"] = std::make_unique<RedLeeverFactory>();

	return true;
}

// Search for object and return new instance of it
std::unique_ptr<Object> GameAssetLibrary::Search(std::string libName)
{
	std::map<std::string, std::unique_ptr<ObjectFactory>>::iterator libIter = library.find(libName);
	if (libIter == library.end())
		return nullptr;

	return libIter->second->create();
}