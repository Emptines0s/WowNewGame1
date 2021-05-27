#pragma once
#include "Unit.h"
class Projectile :
	public Unit
{
public:
	sf::Vector2f c_pos;
	float CurrentFrame = 0;
	
	Projectile(
		std::string name,
		double ms,
		double hp,
		sf::Vector2f pos,
		sf::Image& image,
		sf::Vector2f c_pos
	) : Unit(
		name,
		ms,
		hp,
		pos,
		image
	) {
		this->c_pos = c_pos;
	}
	
	void Move(sf::Time time)
	{
		double dx = (c_pos.x - pos.x);
		double dy = (c_pos.y - pos.y);
		double x_speed = dx / (abs(dx) + abs(dy));
		double y_speed = dy / (abs(dx) + abs(dy));
		sprite.move(sf::Vector2f(x_speed * 0.5 * ms * time.asMilliseconds(), y_speed * 0.5 * ms * time.asMilliseconds()));
	}

	void Animation(sf::Time time)
	{
		CurrentFrame += 0.005 * time.asMilliseconds();
		if (CurrentFrame > 3) CurrentFrame = 0;
		this->sprite.setTextureRect(sf::IntRect(25 * int(CurrentFrame), 0, 25, 25));
		this->sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
	}
	
	void update(sf::Time time)
	{
		Move(time);
		Animation(time);
	}
};

