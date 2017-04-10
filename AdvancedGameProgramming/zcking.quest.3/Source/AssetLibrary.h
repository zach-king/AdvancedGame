#pragma once

#include "GraphicsDevice.h"
#include "Texture.h"
#include "Component.h"
#include "Definitions.h"

#include <map>
#include <memory>
#include <string>

class AssetLibrary
{
public:
	AssetLibrary();
	~AssetLibrary();

	// Initialize texture and physics library from xml files
	bool InitializeLibraries(std::string artXmlFile, std::string physicsXmlFile);

	// Add texture with textureId and texture path
	bool AddTexture(std::string, std::string);
	bool AddPhysicsIntializer(std::string objName, GAME_OBJECTFACTORY_INITIALIZERS inits);

	bool Initialize(GraphicsDevice*);

	// Find and return texture from its textureId
	std::shared_ptr<Texture> SearchTexture(std::string);
	bool SearchPhysics(std::string, GAME_OBJECTFACTORY_INITIALIZERS*);

	// Helper for getting the path from a texture from textureId
	std::string GetTexturePath(std::string assetName);

private:
	std::map<std::string, std::shared_ptr<Texture>> textureLibrary;				// Map textureIds to Texture
	std::map<std::string, GAME_OBJECTFACTORY_INITIALIZERS> physicsLibrary;		// Map object name to physics initializers 
	GraphicsDevice* gDevice;	// Graphics Device used for loading textures

	// Helpers for parsing 
	GAME_BODY_TYPE ParseBodyType(std::string bdType);
	GAME_OBJECT_SHAPE ParseBodyShape(std::string bdShape);
};
