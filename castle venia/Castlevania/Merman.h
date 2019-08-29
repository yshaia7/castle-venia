#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Enemy.h"

//- - - - - - - - - - - - #define sectoin - - - - - - 
#define MOVEMENT_SPEED 1
#define JUMPING_HEIGHT 9
#define SPRITE_HEIGHT 32
#define SPRITE_WIDTH 16
#define WALKING_FRAMES 2
#define FIRE_DELAY 20
#define MAX_HEALTH 2
#define RESPAWN_RANGE 100

class Merman : public Enemy
{
public:
	Merman(sf::Vector2f startLocation, ResourceManager& rManager);
	~Merman() {}

	void playerInteraction(std::weak_ptr<Player> player);
	void spawnEnemy();
	void update();
	void setTexture(ResourceManager & rManager);
	

private:
	int m_fireDelay;
	float m_nextRespawnTime;
	float m_timeUntilShooting;
	bool m_hasJumped;
	bool m_shootTimerActive;
	bool m_isShooting;
	sf::Clock m_respawnTimer;
	sf::Clock m_shootTimer;
	sf::Texture m_fireballTexture;
	void shootFireball();
	void destroy();
};

