#pragma once 
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Range.h"

// - - - - - - - - - - - - - define section - - - - - -
#define SPRITE_WIDTH 17
#define SPRITE_HEIGHT 9

class Dagger : public Range
{
public:
	Dagger() {}
	Dagger(sf::Vector2f origin, int direction);
	~Dagger();
	sf::Vector2f getWeaponSize() { return sf::Vector2f(SPRITE_WIDTH, SPRITE_HEIGHT); }

private:
	void update();
};

