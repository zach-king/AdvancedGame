#include "MagicRoom.h"
#include "Room.h"
#include "RoomMap.h"

#include <iostream>
#include <vector>

Room* MagicRoom::execute(RoomMap *roomMap, int &health)
{
	// Output to player
	std::cout << "You hear loud grinding sounds and you feel your strength restored!" << std::endl;

	// If player has any items, tell them about their items being dispersed,
	// and disperse the inventory items randomly
	if (!roomMap->getInventory().empty())
	{
		std::cout << "In the midst of the commotion, your items have been scattered across the dungeon!" << std::endl;
		roomMap->disperseInventory();
	}

	// Increment health by 2 and randomize the rooms
	health += 2;
	roomMap->randomizeRooms();

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
	// but to counter health increment, decrement it here.
	// This keeps us in the same place. Like walking into a wall...
	if (neighbors.find(transition) == neighbors.end())
	{
		health -= 2;

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

	// Get the next room
	Room* nextRoom = roomMap->findNext(this);
	roomMap->setCurrentRoom(nextRoom);
	return nextRoom;
}

std::string MagicRoom::getType()
{
	return "Magic";
}