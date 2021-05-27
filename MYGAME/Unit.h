#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "string"

class Unit
{
public:
	std::string name;
	double ms;
	double hp;
	sf::Vector2f pos;
	sf::Texture texture;
	sf::Sprite sprite;
	float height;
	float width;
	enum State
	{
		STAY,
		LEFT,
		RIGHT,
		UP,
		DOWN,
		ATTACK,
		STUN,
	} state;


	Unit(std::string name, double ms, double hp, sf::Vector2f pos, sf::Image& image)
	{
		this->name = name;
		this->ms = ms;
		this->hp = hp;
		this->pos = pos;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		height = sprite.getTextureRect().height / 2;
		width = sprite.getTextureRect().width / 2;
		sprite.setOrigin(width, height);
		sprite.setPosition(pos);
	}

	~Unit()
	{
		//std::cout << "Unit die((( ";
	}
	
	virtual void update(sf::Time time) {};
	virtual void update(sf::Time time, sf::Vector2f player_position) {};
};