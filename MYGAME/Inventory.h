#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "string"
#include "Unit.h"
#include "Item.h"
using namespace std;

class Inventory
{
public:
	bool isOpen;
	Unit *owner;
	std::vector <Item*> InventoryItemList;
	sf::Texture InventoryBackground;
	sf::Sprite S_InventoryBackground;
	sf::Texture InventorySlots;
	sf::Sprite S_InventorySlots;
	sf::Time CooldownTime;

	Inventory(bool isOpen, sf::Image& background_image, sf::Image& slots_image, Unit *owner)
	{
		this->isOpen = isOpen;
		this->owner = owner;
		InventoryBackground.loadFromImage(background_image);
		S_InventoryBackground.setTexture(InventoryBackground);
		InventorySlots.loadFromImage(slots_image);
		S_InventorySlots.setTexture(InventorySlots);
	}

	void Open(sf::Time time)
	{
		if (CooldownTime.asMilliseconds() > 0) CooldownTime -= time;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && 	CooldownTime.asMilliseconds() <= 0)
		{
			if (isOpen == true)
			{
				isOpen = false;
				CooldownTime = sf::milliseconds(300);
			}
			else
			{
				isOpen = true;
				CooldownTime = sf::milliseconds(300);
			}
		}
	}
	
	void EqipItem(Item* item)
	{
		owner->hp += item->hp;
	}

	void UneqipItem(Item* item)
	{
		owner->hp -= item->hp;
	}
	
	void SelectItem(sf::RenderWindow& window)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			for (auto item : InventoryItemList)
			{
				if (item->sprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{
					for (auto selectItem : InventoryItemList)
					{
						if (selectItem != item && selectItem->itemtype == item->itemtype && selectItem->isSelect == true) selectItem->isSelect = false, UneqipItem(selectItem);
					}
					if (item->isSelect == true) item->isSelect = false, UneqipItem(item);
					else item->isSelect = true, EqipItem(item);
				}
			}
		}
	}
	
	void update(sf::Time time, sf::RenderWindow& window)
	{
		Open(time);
		if (isOpen == true)
		{
			SelectItem(window);
		}
		for (auto item : InventoryItemList)
		{
			item->update(time, owner);
		}
	}
};