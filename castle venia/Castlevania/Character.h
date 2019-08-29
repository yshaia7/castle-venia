#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 

#include "Mobile.h"
#include "Weapon.h"
#include <vector>

// - - - - - - - - - - - - - enum section - - - - - -
enum DIRECTION {LEFT, RIGHT};

class Character : public Mobile
{
public:
	Character();
	~Character();
	virtual void move(DIRECTION direction); //Change movement direction
	virtual void update() override; //Update character's state
	void draw(sf::RenderWindow& window); 
	void getHit(std::weak_ptr<Character> hitChar); //Get hit by player/enemy
	int getStrength() { return m_strength; } //Return character's strength
	void disableWeapons() { m_attacks.clear(); } //Remove character's weapons

protected:
	bool m_isMoving;
	bool m_isAttacking;
	bool m_isInvincible;
	sf::Clock m_invincibilityTimer; //A period of invincibility after being hit
	DIRECTION m_direction; //Moving direction
	DIRECTION m_animationDirection; //Decided whether we move left or right on the sprite sheet during animations
	int m_health;
	int m_strength; //How much damage the character causes
	int m_maxWeapons; //Max amount of shots allowed on screen at a time
	float m_movementSpeed;
	float m_jumpingHeight;
	std::vector<std::shared_ptr<Weapon>> m_attacks; //List of the character's attacks that are currently on the screen
	virtual void jump();
	virtual void attack(std::shared_ptr<Weapon> weapon);
	virtual void flip(DIRECTION direction); //Flip sprite
	virtual void animate() {}
	void rewindingAnimation(int numOfFrames, int spriteWidth, int spriteHeight, int spriteY); //Once the animation reaches the last frame, it starts playing backwards
};

