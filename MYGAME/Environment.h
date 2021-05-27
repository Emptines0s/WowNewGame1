#pragma once
#include "Unit.h"

class Environment :
	public Unit
{
public:
	bool EventAction;
	
	Environment(
		std::string name,
		double ms,
		double hp,
		sf::Vector2f pos,
		sf::Image& image,
		bool EventAction
	) : Unit(
		name,
		ms,
		hp,
		pos,
		image
	) {
		this->EventAction = EventAction;
	}

};

