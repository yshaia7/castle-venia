#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Weapon.h"

class Melee : public Weapon
{
public:
	Melee(sf::Vector2f origin, sf::Vector2f size) : Weapon(origin) { m_hitbox.setSize(size); }
	~Melee() {};
protected:
	sf::Vector2f m_size;
};

