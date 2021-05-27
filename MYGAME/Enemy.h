#pragma once
#include "Unit.h"

class Slime :
	public Unit
{
public:
	int AttackDamage;
	sf::Time AttackCooldownTime;
	float CurrentFrame = 0;
	
	Slime(
		std::string name,
		double ms,
		double hp,
		sf::Vector2f pos,
		sf::Image& image,
		int AttackDamage
	) : Unit(
		name,
		ms,
		hp,
		pos,
		image
	) {
		this->AttackDamage = AttackDamage;
	}

	void Attack(sf::Time time, sf::Vector2f player_position)
	{	
		state = STAY;

		if (AttackCooldownTime.asMilliseconds() > 0) AttackCooldownTime -= time;

		if (AttackCooldownTime.asMilliseconds() <= 0) {
			if (abs(sprite.getPosition().x - player_position.x) <= 30 && abs(sprite.getPosition().y - player_position.y) <= 30)
			{
				state = ATTACK;
				AttackCooldownTime = sf::milliseconds(1000);
			}
		}
	}
	
	void Move(sf::Time time, sf::Vector2f player_position)
	{
		if (abs(sprite.getPosition().x - player_position.x) > 30 || abs(sprite.getPosition().y - player_position.y) > 30)
		{
			double dx = (player_position.x - sprite.getPosition().x);
			double dy = (player_position.y - sprite.getPosition().y);
			double x_speed = dx / (abs(dx) + abs(dy));
			double y_speed = dy / (abs(dx) + abs(dy));

			sprite.move(sf::Vector2f(x_speed * 0.3 * ms * time.asMilliseconds(), y_speed * 0.3 * ms * time.asMilliseconds()));
		}
	}

	void Animation(sf::Time time)
	{
		CurrentFrame += 0.005 * time.asMilliseconds();
		if (CurrentFrame > 4) CurrentFrame = 0;
		this->sprite.setTextureRect(sf::IntRect(50 * int(CurrentFrame), 0, 50, 50));
		this->sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
	}

	void update(sf::Time time, sf::Vector2f player_position)
	{
		Move(time, player_position);
		Attack(time, player_position);
		Animation(time);
		//std::cout << AttackCooldownTime.asMilliseconds() << "\n";
	}
};