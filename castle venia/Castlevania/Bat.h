#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 

#include "Enemy.h"
//- - - - - - - - - - - - #define sectoin - - - - - - 
#define MOVEMENT_SPEED 0.9
#define SPRITE_HEIGHT 16
#define SPRITE_WIDTH 16
#define WALKING_FRAMES 3
#define FLIGHT_ARC_LIMITER 20
#define MAX_HEALTH 2


class Bat : public Enemy
{
public:
	Bat(sf::Vector2f startLocation, ResourceManager& rManager);
	~Bat();
	void environmentCollisions(std::vector<sf::RectangleShape>& rect) {};
	
	

private:
	void setTexture(ResourceManager& rManager);
	void update();

	int m_flightArcCounter;
};



