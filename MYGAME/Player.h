#pragma once
#include "Unit.h"
#include "Inventory.h"

class Player :
	public Unit
{
public:
	sf::Sprite weaponSelect;

	Player(
		std::string name,
		double ms,
		double hp,
		sf::Vector2f pos,
		sf::Image& image
	) : Unit(
		name,
		ms,
		hp,
		pos,
		image
	) {
		//sprite.setScale(sf::Vector2f(5, 5));
	}
	
	void StatsUpdate()
	{
		
	}
	
	void Control()
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			state = LEFT, ms = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			state = RIGHT, ms = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			state = UP, ms = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			state = DOWN, ms = 1;
		}
		/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			state = ATTACK;
		}*/
	}

	void Animation()
	{
		
	}

	void update(sf::Time time)
	{
		Control();
		switch (state)
		{
		case LEFT: pos.x -= ms * 0.5 * time.asMilliseconds(); break;
		case RIGHT: pos.x += ms * 0.5 * time.asMilliseconds(); break;
		case UP: pos.y -= ms * 0.5 * time.asMilliseconds(); break;
		case DOWN: pos.y += ms * 0.5 * time.asMilliseconds(); break;
		case STAY: break;
		default:
			break;
		}
		sprite.setPosition(pos);
		ms = 0;
		//std::cout << hp << "\n";
	}
};

