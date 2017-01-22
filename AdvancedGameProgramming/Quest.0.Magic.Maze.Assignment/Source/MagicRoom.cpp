#include "MagicRoom.h"
#include "Room.h"
#include "RoomMap.h"

#include <iostream>

Room* MagicRoom::execute(RoomMap *roomMap, int &health)
{
	std::cout << "You hear loud grinding sounds and you feel your strength restored!" << std::endl;
	health += 2;
	roomMap->randomizeRooms();

	// Display the screen output
	std::cout << "View:\t" << description << std::endl;
	std::cout << "Health: " << health << std::endl << std::endl;
	std::cout << "Available Moves: ";
	for each (auto neighbor in neighbors)
	{
		std::cout << neighbor.first << " ";
	}
	std::cout << std::endl << std::endl;
	std::cout << "Select Move: ";

	// Get the user input transition
	std::cin >> transition;

	// Get the name of the next room based off of transition
	std::string nextRoom = next();
	if (nextRoom == "")
		return this;
	else
		return roomMap->getRoom(nextRoom);
}