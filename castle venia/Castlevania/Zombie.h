#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Enemy.h"

//- - - - - - - - - - - - #define sectoin - - - - - - 
#define MOVEMENT_SPEED 1
#define SPRITE_HEIGHT 32
#define SPRITE_WIDTH 16
#define WALKING_FRAMES 2
#define MAX_HEALTH 2

class Zombie : public Enemy
{
public:
	Zombie(sf::Vector2f startLocation, ResourceManager& rManager);
	~Zombie();
	void playerInteraction(std::weak_ptr<Player> player);
	void update();
	void setTexture(ResourceManager& rManager);

private:
};

