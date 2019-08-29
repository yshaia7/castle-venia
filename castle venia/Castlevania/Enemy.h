#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Character.h"
#include "Player.h"
#include "Fireball.h"

class Enemy : public Character, public std::enable_shared_from_this<Enemy>
{
public:
	Enemy() {}
	Enemy(sf::Vector2f startLocation, ResourceManager& rManager);
	~Enemy();
	virtual void playerInteraction(std::weak_ptr<Player> player); //Act based on player state
	virtual void spawnEnemy(); //Appear in a specific location
	void restoreHealth() { m_health = m_maxHealth; }
	void setMaxHealth(int newMax) { m_maxHealth = newMax; }
	void update();
	virtual int getHealth() { return m_health; }
	int getPoints() { return m_points; }
	

protected:
	int m_spawnDistanceMin, m_spawnDistanceMax; //The range in which an enemy appears, and when it disappears
	sf::Vector2f m_initialLocation; //Starting location
	int m_points; //How many points the player will get for killing the enemy

private:
	int m_maxHealth;
};

