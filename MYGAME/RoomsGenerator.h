#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "string"
#include "Unit.h"
using namespace std;
class RoomsGenerator
{
public:

	bool doorCheck = false;
	int room_height, room_width, slimeCount;
	sf::Vector2i doors_position;
	
	char RandTile()
	{
		int randtile = rand() % 30 + 1;
		if (randtile >= 1 && randtile <= 29) return 'G';
		if (randtile >= 30 && randtile <= 30 && slimeCount != 0)
		{
			slimeCount--;
			return 'S';
		}
	}

	char DoorSpawn(int param)
	{
		int doorspawn = rand() % param + 1;
		if (doorspawn >= 1 && doorspawn <= param - 3) return 'W';
		if (doorspawn >= param - 2 && doorspawn <= param)
		{
			doorCheck = true;
			return 'D';
		}
	}
	
	void Generate(vector < vector <char> >& Room)
	{
		doorCheck = false;
		room_height = rand() % 7 + 10;
		room_width = rand() % 7 + 10;
		slimeCount = int(room_height * room_width * 0.02);
		cout << "SLIME COUNT" << slimeCount << "\n";
		for (int i = 0; i < room_height; i++) {
			Room.push_back(vector <char>());
			for (int j = 0; j < room_width; j++)
			{
				if (doorCheck == false && (i == (room_height - 1)) && (j == (room_width - 2)))
				{
					Room[i].push_back('D');
					doorCheck = true;
				}
				else
				if (i == 0 || i == room_height - 1 || j == 0 || j == room_width - 1)
				{
					if (doorCheck == false && i != 0 && j != 0)
					{
						Room[i].push_back(DoorSpawn((room_height * 2 + room_width * 2) - 2));
					}
					else Room[i].push_back('W');
				}
				else
				{
					Room[i].push_back(RandTile());
				}

			}
		}
		for (int i = 0; i < room_height; i++) {
			Room.push_back(vector <char>());
			for (int j = 0; j < room_width; j++)
			{
				cout << Room[i][j];
			}
			cout << "\n";
		}
		std::cout << room_height << " | " << room_width << "\n";
	}
};

