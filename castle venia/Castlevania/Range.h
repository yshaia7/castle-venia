#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Weapon.h"

class Range : public Weapon
{
public:
	Range() {};
	Range(sf::Vector2f origin, int direction) : Weapon(origin) { m_direction = direction; }
	~Range() {};
protected:
	int m_direction;
};

