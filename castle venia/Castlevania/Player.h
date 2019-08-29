#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Character.h"
#include "Weapon.h"
#include "Melee.h"
#include "Dagger.h"
#include "Axe.h"
#include "Boomerang.h"

// - - - - - - - - - - - - - const section - - - - - -
#define MOVEMENT_SPEED 1.8
#define JUMP_HEIGHT 4.5
#define MAX_HEALTH 16
#define MAX_LIVES 5
#define HITBOX_HEIGHT 31
#define HITBOX_WIDTH 16
#define SPRITE_WIDTH 60
#define SPRITE_HEIGHT 32
#define CROUCHING_HEIGHT 23
#define WALKING_FRAMES 3 //How many frames there are in the walking animation
#define ATTACKING_FRAMES 3
#define STAIRS_DELAY 10 //The amount of delay between frames in the climbing animation
#define INVINCIBILITY_TIME 1.5 //Time invincible after getting hit (in seconds)
#define LEVEL_TIME 300 //The time limit for a level
#define DEFAULT_HEARTS 50


class Player : public Character, public std::enable_shared_from_this<Player>
{
public:
	Player(ResourceManager& rManager);
	~Player();
	void environmentCollisions(std::vector<sf::RectangleShape>& rect);
	int getWeaponType() { return m_weaponHeld; }
	int getHealth() { return m_health; }
	void restoreHealth() { m_health = MAX_HEALTH; }
	int getHearts() { return m_hearts; }
	void addHearts(int addHearts);
	void resetHearts() { m_hearts = DEFAULT_HEARTS; }
	int getLives() { return m_lives; }
	void setLives(int lives) { m_lives = lives; }
	void resetLives() { m_lives = MAX_LIVES; }
	void addScore(int score) { m_score += score; }
	void resetScore() { m_score = 0; }
	int getScore() { return m_score; }
	void defaultState(); //Reset character's hitboxes and animations to a default state
	void getButtonPress(sf::Keyboard::Key key);
	void getButtonRelease(sf::Keyboard::Key key);
	void useWhip();
	void updgradeWhip();
	int getWhipLevel() { return m_whipLevel; }
	void resetWhip() { m_whipLevel = 1; }
	void setWeapon(int newWeapon); //Change current weapon held
	std::tuple<sf::Texture&, int, int> getWeapon() { return std::tuple<sf::Texture&, int, int>(m_currentSubweapon, m_subweaponTextureSize.x, m_subweaponTextureSize.y); } //Return current weapon's texture and its sizes
	void setClimbing(sf::Vector2f startLocation, int numOfStairs, DIRECTION direction, int elevation); //Prepare to climb on stairs
	sf::Vector2f getWhipSize();
	void update(std::vector<sf::RectangleShape>& rect);
	const sf::Vector2f& getLocation() { return m_hitbox.getPosition(); }
	void collectItem(int itemType); //Get new item. 0 = Food, 1 = small heart, 2 = large heart
	void colletWeapon(int weaponType) { m_weaponHeld = weaponType; } //Get new weapon
	void checkAttackTarget(std::weak_ptr<Object> obj); //Check state of the character that was attacked by the player
	void getHit(std::weak_ptr<Character> hitChar);
	bool getDamagedState() { return m_isDamaged; }
	bool getFallingState() { return m_falling; }
	bool checkInaction() { return !(m_isAttacking || m_isThrowing || m_isDamaged || m_velocity.x != 0 || m_velocity.y != 0 || m_falling || m_climbing); } //Check if the player is currently performing some kind of action
	bool getClimbingState() { return m_climbing; }
	void draw(sf::RenderWindow& window);
	void die();
	void automatedMovement(DIRECTION direction); //Special movement that's controlled by the game
	void resetTimer(); //Reset game timer
	int getTime() { return m_remainingTime; }
	void setCameraLock(bool state) { m_cameraLock = state; }
	bool getCameraLock() { return m_cameraLock; }
	void setLevelClearState(bool state) { m_levelClear = state; }
	bool getLevelClearState() { return m_levelClear; }

private:
	void setTexture(ResourceManager& rManager);
	void setCrouch(bool newState) { m_crouching = newState; }
	bool m_isAttacking;
	bool m_isThrowing;
	bool m_isDamaged;
	bool m_crouching;
	bool m_climbing; //Climbing the stairs
	bool m_stairStanding; //Currently standing on the stairs
	bool m_deathAnimation;
	bool m_cameraLock;
	bool m_levelClear;
	bool m_moveBeforeJumping; //Shows that the character pressed left or right before jumping, which allows air movement (can't change direction or move after executing a jump)
	int m_currentStair; //The current stair you're standing on
	int m_totalStairs; //Total stairs in a staircase
	int m_stairsElevation; //Whether you're going up or down on a staircase
	int m_invincibilityDelay;
	int m_weaponHeld; // 0 = nothing, 1 = dagger, 2 = axe, 3 = boomerang, 4 = holyWater
	int m_whipLevel; //Changes whip size
	int m_hearts; //Used as ammunition for weapons
	int m_score;
	int m_lives;
	double m_remainingTime;
	sf::Texture m_daggerTexture;
	sf::Texture m_axeTexture;
	sf::Texture m_hWaterTexture;
	sf::Texture m_boomerangTexture;
	sf::Texture m_currentSubweapon;
	sf::Texture m_emptyTexture;
	sf::Clock m_levelTime;
	sf::Vector2f m_subweaponTextureSize;
	ResourceManager* m_resources;
	void animate(); //Animate character baesd on different movements
	void animateWhip();
	void throwWeapon();
	void climbStairs();
	void jump();
};

