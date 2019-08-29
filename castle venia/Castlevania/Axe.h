#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Range.h"

// - - - - - - - - - - - - - define section - - - - - -
#define NUM_OF_FRAMES 4
#define SPRITE_WIDTH 15
#define SPRITE_HEIGHT 14

class Axe : public Range
{
public:
	Axe() {}
	Axe(sf::Vector2f origin, int direction);
	~Axe();
	sf::Vector2f getWeaponSize() { return sf::Vector2f(SPRITE_WIDTH, SPRITE_HEIGHT); }

private:
	void update();
};

