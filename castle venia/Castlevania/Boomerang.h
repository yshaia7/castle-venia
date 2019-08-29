#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Range.h"

// - - - - - - - - - - - - - define section - - - - - -
#define NUM_OF_FRAMES 3
#define SPRITE_WIDTH 15
#define SPRITE_HEIGHT 14
#define SPEED 3

class Boomerang : public Range
{
public:
	Boomerang() {}
	Boomerang(sf::Vector2f origin, int direction);
	~Boomerang();
	void update();
	sf::Vector2f getWeaponSize() { return sf::Vector2f(SPRITE_WIDTH, SPRITE_HEIGHT); }

private:
	float m_returningSpeed;
	bool m_returning;
	sf::Clock m_soundTimer;
};

