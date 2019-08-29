#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Range.h"

class Fireball : public Range
{
public:
	Fireball(sf::Vector2f origin, int direction);
	~Fireball();
};

