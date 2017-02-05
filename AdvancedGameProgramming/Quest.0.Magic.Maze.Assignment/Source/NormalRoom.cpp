#include "NormalRoom.h"
#include "Room.h"
#include "RoomMap.h"

#include <iostream>

Room* NormalRoom::execute(RoomMap *roomMap, int &health)
{
	// Health decrements
	health--;

	// Pick up this Room's item, if it hasn't been picked up yet
	if (item != "")
	{
		roomMap->addItem(item);
		std::cout << "Picked up an item: '" << item << "'" << std::endl << std::endl;
		item = "";
	}

	// Display the screen output
	std::cout << "View:\t" << description << std::endl;
	std::cout << "Health: " << health << std::endl << std::endl;

	// Display inventory
	std::cout << "Inventory:" << std::endl;
	std::vector<std::string> items = roomMap->getInventory();
	for (auto itemIter = items.begin(); itemIter != items.end(); ++itemIter)
	{
		std::cout << "\t" << *itemIter << std::endl;
	}

	std::cout << "Available Moves: ";
	for each (auto neighbor in neighbors)
	{
		std::cout << neighbor.first << " ";
	}
	std::cout << std::endl << "Enter `p` to save or `o` to load a previous save." << std::endl << std::endl;
	std::cout << "Select Move: ";

	// Get the user input transition
	std::cin >> transition;

	// Validate transition; if invalid,
	// return same Room, because we didn't move
	// but to counter health decrement, increment it here.
	// This keeps us in the same place. Like walking into a wall...
	if (neighbors.find(transition) == neighbors.end())
	{
		health++;

		// Check for save/load
		if (transition == "p")
		{
			roomMap->SaveLevel("Config/gamesave.xml", health);
		}
		else if (transition == "o")
		{
			roomMap->Initialize("Config/gamesave.xml", health);
			return roomMap->getStartRoom();
		}

		return this;
	}

	// Get the name of the next room based off of transition
	Room* nextRoom = roomMap->findNext(this);
	roomMap->setCurrentRoom(nextRoom);
	return nextRoom;
}

// Overrode getter for Normal Room type
std::string NormalRoom::getType()
{
	return "Normal";
}