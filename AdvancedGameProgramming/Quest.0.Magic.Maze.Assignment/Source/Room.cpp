#include "Room.h"
#include"definitions.h"

#include<map>
#include<string>

#include"ThirdParty\tinyxml\tinystr.h"
#include"ThirdParty\tinyxml\tinyxml.h"

Room::Room()
{
	canHaveItem = false;
	item = "";
}

Room::~Room()
{
	// Nothing
}

bool Room::getCanHaveItem()
{
	return canHaveItem;
}

std::string Room::getItem()
{
	return item;
}

void Room::setItem(std::string itemName)
{
	item = itemName;
}

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
		canHaveItem = true;
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

bool Room::finish()
{
	return (condition == WIN || condition == LOSE || condition == QUIT);
}

std::string Room::next()
{
	// Return the appropriate Room identifier for the given 
	// transition keyword, if the Room exists.
	if (neighbors.find(transition) != neighbors.end())
		return neighbors.find(transition)->second;
	return "";
}

void Room::setIdentifier(std::string ident)
{
	identifier = ident;
}

void Room::setDescription(std::string desc)
{
	description = desc;
}

std::string Room::getIdentifier()
{
	return identifier;
}

END_CONDITION Room::getCondition()
{
	return condition;
}

void Room::addNeighbor(std::string transition, std::string roomName)
{
	neighbors[transition] = roomName;
}

void Room::clearNeighbors()
{
	// Clear all the neighbors but keep the quit option
	neighbors.clear();
	neighbors["q"] = "quit";
}

std::map<std::string, std::string> Room::getNeighbors()
{
	return neighbors;
}