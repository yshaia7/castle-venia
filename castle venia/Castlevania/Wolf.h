#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Enemy.h"

//- - - - - - - - - - - - #define sectoin - - - - - - 
#define MOVEMENT_SPEED 3
#define JUMPING_HEIGHT 4
#define SPRITE_HEIGHT 16
#define SPRITE_WIDTH 32
#define WALKING_FRAMES 3
#define MAX_HEALTH 2
#define AWAKENING_DISTANCE 50


class Wolf : public Enemy
{
public:
	Wolf(sf::Vector2f startLocation, ResourceManager& rManager);
	~Wolf();
	
	void playerInteraction(std::weak_ptr<Player> player);
	void spawnEnemy();
	void update();
	void setTexture(ResourceManager & rManager);

private:
	bool m_isAwake;
	bool m_landed;
};

