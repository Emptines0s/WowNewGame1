#pragma once
#include <SFML/Graphics.hpp>
#include "Unit.h"
#include "Item.h"
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;


class CollisionCheck
{
public:

	void Collision(vector <Item*>& InventoryItemList, list <Unit*>& unit, list <Unit*>::iterator obj1, list <Unit*>::iterator obj2, sf::RenderWindow& window, bool& nextRoom, sf::Time time, int& enemyCount)
	{
		
		for (obj1 = unit.begin(); obj1 != unit.end(); obj1++)
		{
			for (obj2 = unit.begin(); obj2 != unit.end();)
			{
				if ((*obj1)->sprite.getGlobalBounds().intersects((*obj2)->sprite.getGlobalBounds()) && (*obj1)->name == "player" && (*obj2)->name == "slime" && (*obj2)->state == 5)
				{
					(*obj1)->hp -= 1;
				}
				if ((*obj1)->sprite.getGlobalBounds().intersects((*obj2)->sprite.getGlobalBounds()) && (*obj1)->name == "EmeraldStaff_Projectile" && (*obj2)->name == "slime")
				{
					(*obj1)->hp -= 1;
					(*obj2)->hp -= 1;
				}
				if ((*obj1)->sprite.getGlobalBounds().intersects((*obj2)->sprite.getGlobalBounds()) && (*obj1)->name == "EmeraldStaff_Projectile" && ((*obj2)->name == "Wall" || (*obj2)->name == "Door"))
				{
					(*obj1)->hp -= 1;
				}
				if ((*obj1)->sprite.getGlobalBounds().intersects((*obj2)->sprite.getGlobalBounds()) && (*obj1)->name == "player" && (*obj2)->name == "Door" && enemyCount == 0)
				{
					nextRoom = true;
					(*obj1)->pos = sf::Vector2f(60, 100);
					(*obj1)->hp +=5;
				}
				if ((*obj1)->sprite.getGlobalBounds().intersects((*obj2)->sprite.getGlobalBounds()) && (*obj1)->name == "player" && (*obj2)->name == "Wall")
				{
					if ((*obj1)->state == 1)
					{
						(*obj1)->pos.x += 1 * 0.5 * time.asMilliseconds();
					}
					if ((*obj1)->state == 2)
					{
						(*obj1)->pos.x -= 1 * 0.5 * time.asMilliseconds();
					}
					if ((*obj1)->state == 3)
					{
						(*obj1)->pos.y += 1 * 0.5 * time.asMilliseconds();
					}
					if ((*obj1)->state == 4)
					{
						(*obj1)->pos.y -= 1 * 0.5 * time.asMilliseconds();
					}
					//cout << (*obj1)->state << "\n";
				}
				if ((*obj1)->sprite.getGlobalBounds().intersects((*obj2)->sprite.getGlobalBounds()) && (*obj1)->name == "player" && ((*obj2)->name == "staff" || (*obj2)->name == "helmet" || (*obj2)->name == "boots" || (*obj2)->name == "armor"))
				{	
					InventoryItemList.push_back((Item*)(*obj2));
					obj2 = unit.erase(obj2);
				}
				else obj2++;
			}
		}
	}
};

