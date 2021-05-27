#pragma once
#include <SFML/Graphics.hpp>
#include "Item.h"
#include "Inventory.h"
#include <iostream>
#include <list>
#include <algorithm>
#include "string"
using namespace std;

class RenderLayers
{
public:

	sf::RectangleShape player_hpBar;

	void Render(Inventory inventory, vector <Item*>& InventoryItemList, list <Unit*>& unit, list <Unit*>::iterator obj1, list <Unit*>::iterator obj2, sf::RenderWindow& window, int player_hp)
	{
		
		unit.sort([](Unit* obj1, Unit* obj2)
		{
			return (*obj1).pos.y < (*obj2).pos.y;
		});
		
		for (obj1 = unit.begin(); obj1 != unit.end(); obj1++)
		{
			if ((*obj1)->name == "Ground") window.draw((*obj1)->sprite);
		}
		
		for (obj1 = unit.begin(); obj1 != unit.end(); obj1++)
		{
			if ((*obj1)->name != "Ground") window.draw((*obj1)->sprite);
		}


		window.setView(window.getDefaultView());

		if (inventory.isOpen == true)
		{
			window.draw(inventory.S_InventoryBackground);

			int ItemIndex = 0;
			for (auto item : InventoryItemList)
			{
				if (item->isSelect == false)
				{
					ItemIndex++;
					item->sprite.setPosition(ItemIndex * 55, 500);
					inventory.S_InventorySlots.setPosition(item->sprite.getPosition().x - item->width, item->sprite.getPosition().y - item->height);
					window.draw(inventory.S_InventorySlots);
				}
				else 
				{
					switch (item->itemtype)
					{
					case Item::WEAPON: item->sprite.setPosition(150, 150); break;
					case Item::HELMET: item->sprite.setPosition(150, 210); break;
					case Item::CHEAST: item->sprite.setPosition(150, 270); break;
					case Item::BOOTS: item->sprite.setPosition(150, 330); break;
					default:
						break;
					}
				}
				window.draw(item->sprite);
			}
		}
		player_hpBar.setSize(sf::Vector2f(player_hp, 20));
		player_hpBar.setFillColor(sf::Color::Green);
		player_hpBar.setPosition(600, 50);
		window.draw(player_hpBar);
	}
};