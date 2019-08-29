#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Enemy.h"

//- - - - - - - - - - - - #define sectoin - - - - - - 
#define WALKING_FRAMES 2
#define MAX_HEALTH 16
#define MOVEMENT_SPEED 1.5
#define SPRITE_WIDTH 48
#define SPRITE_HEIGHT 23
#define FLIGHT_ARC_LIMITER 10
#define DEATH_ANIMATION_LOOP 3
#define ATTACK_INTERVAL 2
#define ATTACKING_SPEED 2.5
#define STRENGTH 3

class GiantBat : public Enemy
{
public:
	GiantBat(sf::Vector2f startLocation, ResourceManager& rManager, std::vector<int>bounds);
	~GiantBat();
	void setTexture(ResourceManager& rManager);
	void playerInteraction(std::weak_ptr<Player> player);
	void update();
	void draw(sf::RenderWindow& window);

private:
	std::vector<int> m_bounds;
	int m_flightArcCounter = 0;
	int m_deathAnimationCounter;
	float m_flightAltitude;
	sf::Clock m_attackTimer;
	sf::Clock m_battleStartTimer;
	sf::Vector2f m_target; //Player location
	bool m_midAttack;
	bool m_timerStarted;
	void swoop(); //Attack player
};

