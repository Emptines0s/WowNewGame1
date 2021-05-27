#pragma once
#include "Unit.h"

class Item :
	public Unit
{
public:
	enum ItemType
	{
		WEAPON,
		HELMET,
		CHEAST,
		BOOTS,
	} itemtype;
	int ItemID;
	bool onGround;
	bool isSelect;
	sf::Time AttackCooldownTime;

	Item(
		std::string name,
		double ms,
		double hp,
		sf::Vector2f pos,
		sf::Image & image,
		ItemType itemtype,
		int ItemID,
		bool onGround
	) : Unit(
		name,
		ms,
		hp,
		pos,
		image
	) {
		this->itemtype = itemtype;
		this->ItemID = ItemID;
		this->onGround = onGround;
		this->isSelect = false;
	}
	
	void EffectsList(sf::Time time, Unit* owner)
	{
		if (this->name == "staff")
		{
			state = STAY;

			if (AttackCooldownTime.asMilliseconds() > 0) AttackCooldownTime -= time;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (AttackCooldownTime.asMilliseconds() <= 0)
				{
					state = ATTACK;
					AttackCooldownTime = sf::milliseconds(1000);
				}
			}
			//std::cout << AttackCooldownTime.asMilliseconds() << "\n";
		}
	}

	void update(sf::Time time, Unit* owner)
	{
		if (isSelect == true)
		{
			EffectsList(time, owner);
		}
	}
};

