#include "Room.h"
#include"definitions.h"

#include<map>
#include<string>

#include"ThirdParty\tinyxml\tinystr.h"
#include"ThirdParty\tinyxml\tinyxml.h"

// Default constructor
Room::Room()
{
	item = "";
}

// Destructor
Room::~Room()
{
	// Nothing
}

// Item getter
std::string Room::getItem()
{
	return item;
}

// Item setter
void Room::setItem(std::string itemName)
{
	item = itemName;
}

// Init room with given XML element
bool Room::Initialize(TiXmlElement *room)
{
	// Set the condition from the xml element <Room>. 
	int cond;
	room->QueryIntAttribute("condition", &cond);
	condition = static_cast<END_CONDITION>(cond);

	// Check validity of XML
	if (room->Attribute("name") == NULL || room->Attribute("description") == NULL)
		return false;

	// Check if there is an item attribute, and add it to the room
	if (room->Attribute("item") != NULL)
	{
		item = room->Attribute("item");
	}

	// Get the name and description from the xml element <Room>
	identifier = room->Attribute("name");
	description = room->Attribute("description");

	// Iterate over the <Neighbor> children elements and add them 
	// to the neighbors map appropriately
	for (auto neighbor = room->FirstChildElement(); neighbor != NULL; neighbor = neighbor->NextSiblingElement())
	{
		addNeighbor(neighbor->Attribute("transition"), neighbor->Attribute("target"));
	}

	return true;
}

// Return true if this room has an end condition
bool Room::finish()
{
	return (condition == WIN || condition == LOSE || condition == QUIT);
}

// Get the string of the name of the next room, from transition
// or none ("") if the neighbor for that transition DNE
std::string Room::next()
{
	// Return the appropriate Room identifier for the given 
	// transition keyword, if the Room exists.
	if (neighbors.find(transition) != neighbors.end())
		return neighbors.find(transition)->second;
	return "";
}

// Setter for name of room
void Room::setIdentifier(std::string ident)
{
	identifier = ident;
}

// Setter for description
void Room::setDescription(std::string desc)
{
	description = desc;
}

// Getter for description
std::string Room::getDescription()
{
	return description;
}

// Getter for name of room
std::string Room::getIdentifier()
{
	return identifier;
}

// Getter for condition
END_CONDITION Room::getCondition()
{
	return condition;
}

// Helper - add a neighbor for a given transition
void Room::addNeighbor(std::string transition, std::string roomName)
{
	neighbors[transition] = roomName;
}

// Helper - clear out all neighbors (used by roomMap for randomizeRooms())
void Room::clearNeighbors()
{
	// Clear all the neighbors but keep the quit option
	neighbors.clear();
	neighbors["q"] = "quit";
}

// Getter for neighbors
std::map<std::string, std::string> Room::getNeighbors()
{
	return neighbors;
}