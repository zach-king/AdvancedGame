#include "NormalRoom.h"
#include "Room.h"
#include "RoomMap.h"

#include <iostream>

Room* NormalRoom::execute(RoomMap *roomMap, int &health)
{
	// Health decrements
	health--;

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