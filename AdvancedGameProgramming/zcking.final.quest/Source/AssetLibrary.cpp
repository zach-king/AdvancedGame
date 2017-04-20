#include "AssetLibrary.h"
#include "tinyxml\tinyxml.h"

AssetLibrary::AssetLibrary()
{

}

AssetLibrary::~AssetLibrary()
{

}

bool AssetLibrary::InitializeLibraries(std::string artXmlFile, std::string physicsXmlFile)
{
	//---------------------------------------------
	// Parse Art information from xml file
	//---------------------------------------------

	// Create the XML document object and 
	// Check if it loaded without trouble
	TiXmlDocument artXml(artXmlFile.c_str());
	if (!artXml.LoadFile())
	{
		printf("Unable to load art XML file %s! Tiny XML Error: %s\n", artXmlFile.c_str(), artXml.ErrorDesc());
		return false;
	}

	// Root and object xml pointers
	TiXmlElement* pRootXML = NULL;
	TiXmlElement* pObjectXML = NULL;

	// Parse the XML object; get the root XML element
	pRootXML = artXml.FirstChildElement("Objects");

	// If is not in config file, exit with error
	if (pRootXML == NULL)
		return false;

	// Parse the art assets out of XML file
	pObjectXML = pRootXML->FirstChildElement("ArtAsset");
	while (pObjectXML != NULL)
	{
		// Get the creature attributes and add to art asset library
		AddTexture(pObjectXML->Attribute("name"), pObjectXML->Attribute("sprite"));

		// Get the next creature element
		pObjectXML = pObjectXML->NextSiblingElement("ArtAsset");
	}



	//---------------------------------------------
	// Parse Physics information from xml file
	//---------------------------------------------
	TiXmlDocument physicsXml(physicsXmlFile.c_str());
	if (!physicsXml.LoadFile())
	{
		printf("Unable to load physics XML file %s! Tiny XML Error: %s\n", artXmlFile.c_str(), artXml.ErrorDesc());
		return false;
	}

	pRootXML = physicsXml.FirstChildElement("Physics");
	if (pRootXML == NULL)
		return false;

	// Parse the physics data from XML file into struct
	GAME_OBJECTFACTORY_INITIALIZERS inits;
	pObjectXML = pRootXML->FirstChildElement("BodyInfo");
	while (pObjectXML != NULL)
	{
		// Query all data
		inits.bodyType = ParseBodyType(pObjectXML->Attribute("type"));
		inits.bodyShape = ParseBodyShape(pObjectXML->Attribute("shape"));
		pObjectXML->QueryFloatAttribute("density", &inits.bodyDensity);
		pObjectXML->QueryFloatAttribute("friction", &inits.bodyFriction);
		pObjectXML->QueryFloatAttribute("restitution", &inits.bodyRestitution);
		pObjectXML->QueryFloatAttribute("angular_damping", &inits.bodyAngDamping);
		pObjectXML->QueryFloatAttribute("linear_damping", &inits.bodyLinDamping);
		pObjectXML->QueryBoolAttribute("bullet", &inits.bodyIsBullet);
		pObjectXML->QueryBoolAttribute("rotate", &inits.bodyRotates);
		inits.category = pObjectXML->Attribute("category");

		// Add the data to the library
		std::string objName = pObjectXML->Attribute("object");
		physicsLibrary[pObjectXML->Attribute("object")] = inits;

		// Move XML pointer to next 
		pObjectXML = pObjectXML->NextSiblingElement("BodyInfo");
	}

	// Done loading data! 
	return true;
}

bool AssetLibrary::Initialize(GraphicsDevice* gDev)
{
	gDevice = gDev;
	return true;
}

bool AssetLibrary::AddTexture(std::string assetName, std::string path)
{
	// Make new texture and load it from the path given
	std::shared_ptr<Texture> tex(std::make_shared<Texture>());
	if (!tex->load(gDevice->getRenderer(), path))
		return false;

	// Store the new texture in our library
	textureLibrary[assetName] = tex;
	return true;
}

bool AssetLibrary::AddPhysicsIntializer(std::string objName, GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	// Store new physics initializer information in library
	physicsLibrary[objName] = inits;
	return true;
}

std::string AssetLibrary::GetTexturePath(std::string assetName)
{
	// Find the path for the given textureId
	auto assetIter = textureLibrary.find(assetName);
	if (assetIter == textureLibrary.end())
		return "";

	return assetIter->second->getPath();
}

std::shared_ptr<Texture> AssetLibrary::SearchTexture(std::string assetName)
{
	// Find the texture with the given textureId
	auto asset = textureLibrary.find(assetName);
	if (asset == textureLibrary.end())
		return nullptr;

	return asset->second;
}

bool AssetLibrary::SearchPhysics(std::string objName, GAME_OBJECTFACTORY_INITIALIZERS* inits)
{
	auto initsIter = physicsLibrary.find(objName);
	if (initsIter == physicsLibrary.end())
		return false;

	GAME_OBJECTFACTORY_INITIALIZERS tmpInits = initsIter->second;
	inits->bodyType = tmpInits.bodyType;
	inits->bodyShape = tmpInits.bodyShape;
	inits->bodyDensity = tmpInits.bodyDensity;
	inits->bodyFriction = tmpInits.bodyFriction;
	inits->bodyRestitution = tmpInits.bodyRestitution;
	inits->bodyAngDamping = tmpInits.bodyAngDamping;
	inits->bodyLinDamping = tmpInits.bodyLinDamping;
	inits->bodyIsBullet = tmpInits.bodyIsBullet;
	inits->category = tmpInits.category;
	return true;
}


GAME_BODY_TYPE AssetLibrary::ParseBodyType(std::string bdType)
{
	if (bdType == "dynamic")
		return GAME_DYNAMIC;
	else if (bdType == "kinematic")
		return GAME_KINEMATIC;
	else if (bdType == "static")
		return GAME_STATIC;

	return GAME_STATIC; // default to static
}

GAME_OBJECT_SHAPE AssetLibrary::ParseBodyShape(std::string bdShape)
{
	if (bdShape == "rectangle")
		return GAME_RECTANGLE;
	else if (bdShape == "circle")
		return GAME_CIRCLE;

	return GAME_CIRCLE; // default to circle
}
