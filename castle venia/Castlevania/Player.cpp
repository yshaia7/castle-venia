#include "Player.h"
#include "Enemy.h"
#include <typeinfo>

//----------------------------------------------------------
Player::Player(ResourceManager& rManager)
{
	m_isAttacking = false;
	m_isThrowing = false;
	m_isDamaged = false;
	m_crouching = false;
	m_climbing = false;
	m_stairStanding = false;
	m_deathAnimation = false;
	m_cameraLock = false;
	m_levelClear = false;
	m_moveBeforeJumping = false;
	setTexture(rManager);
	setWeapon(0);
	m_whipLevel = 1;
	m_maxWeapons = 1;
	m_direction = RIGHT;
	m_movementSpeed = MOVEMENT_SPEED;
	m_jumpingHeight = JUMP_HEIGHT;
	m_health = MAX_HEALTH;
	m_hearts = 50;
	m_score = 0;
	m_lives = MAX_LIVES;
	m_strength = 2;
	m_currentStair = 0;
	m_invincibilityDelay = 0;
	m_remainingTime = LEVEL_TIME;
}

//----------------------------------------------------------
Player::~Player()
{
}

//----------------------------------------------------------
void Player::setTexture(ResourceManager& rManager)
{
	m_resources = &rManager;
	m_sprite.setTexture(rManager.getPlayerTexture());
	m_hitbox.setSize(sf::Vector2f(HITBOX_WIDTH, HITBOX_HEIGHT));
	m_daggerTexture = rManager.getDaggerTexture();
	m_axeTexture = rManager.getAxeTexture();
	m_boomerangTexture = rManager.getBoomerandTexture();
	m_emptyTexture = rManager.getEmptyTexture();
	setSoundBuffer(rManager.getDamageSound());
	defaultState();
}

//----------------------------------------------------------
void Player::environmentCollisions(std::vector<sf::RectangleShape>& rect)
{
	if (m_climbing || m_stairStanding)
		return;
	Mobile::environmentCollisions(rect);
}

//----------------------------------------------------------
void Player::addHearts(int addHearts)
{
	m_hearts += addHearts;
	if (m_hearts > 99)
		m_hearts = 99;
}

//----------------------------------------------------------
void Player::defaultState()
{
	m_sprite.setTextureRect({ 0,0,SPRITE_WIDTH,SPRITE_HEIGHT });
	m_hitbox.setSize(sf::Vector2f(HITBOX_WIDTH, HITBOX_HEIGHT));
	if (m_sprite.getScale() == sf::Vector2f(1,1))
		m_hitbox.setPosition(m_sprite.getGlobalBounds().left, m_sprite.getGlobalBounds().top);
	else
		m_hitbox.setPosition(m_sprite.getGlobalBounds().left + m_sprite.getGlobalBounds().width - HITBOX_WIDTH, m_sprite.getGlobalBounds().top);
	m_sprite.setColor(sf::Color::White);
}

//----------------------------------------------------------
void Player::getButtonPress(sf::Keyboard::Key key)
{
	//Can't act while in damaged animation or while in the stair climbing animation
	if (m_isDamaged || m_isAttacking || m_isThrowing || (m_climbing && !m_stairStanding)) 
		return;

	//Can't change direction during a jump, while crouching or when attacking
	if (!m_falling && !m_crouching && !m_isAttacking && !m_stairStanding) 
	{
		if (key == sf::Keyboard::Left)
			move(LEFT);
		else if (key == sf::Keyboard::Right)
			move(RIGHT);
		if (key == sf::Keyboard::X)
		{
			jump();
		}
		if (key == sf::Keyboard::Down && !m_stairStanding && !m_climbing)
		{
			setCrouch(true);
		}
	}
	if (m_stairStanding && sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		climbStairs();


	//throw weapon
	if (key == sf::Keyboard::Z && sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !m_stairStanding)
	{
		if (m_weaponHeld == 0 || m_attacks.size() >= m_maxWeapons || m_hearts <= 0)
			return;
		m_animationDirection = RIGHT;
		m_animationDelay = 0;
		m_animationStage = -1;
		m_isThrowing = true;
	}
	//attack with whip
	else if (key == sf::Keyboard::Z)
	{
		m_animationDirection = RIGHT;
		m_animationDelay = 0;
		m_animationStage = -1;
		m_isAttacking = true;
	}
}

//----------------------------------------------------------
void Player::getButtonRelease(sf::Keyboard::Key key)
{
	//Stop horizontal movement
	if (m_velocity.y == 0) //Can't stop movement during a jump
	{
		if (key == sf::Keyboard::Left && m_velocity.x < 0)
		{
			//If left was released while pressing right, go right
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				getButtonPress(sf::Keyboard::Right);
		}
		if (key == sf::Keyboard::Right && m_velocity.x > 0)
		{
			//If right was released while pressing left, go left
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				getButtonPress(sf::Keyboard::Left);
		}
	}
}

//----------------------------------------------------------
void Player::useWhip()
{
	std::shared_ptr<Melee> newMelee;
	//Attack left or right
	if (m_direction == LEFT)
		newMelee = std::make_shared<Melee>(sf::Vector2f( m_hitbox.getGlobalBounds().left - getWhipSize().x,
		m_hitbox.getGlobalBounds().top + 8), getWhipSize());
	else
		newMelee = std::make_shared<Melee>(sf::Vector2f( m_hitbox.getGlobalBounds().left + m_hitbox.getGlobalBounds().width,
			             m_hitbox.getGlobalBounds().top + 8), getWhipSize());
	newMelee->setSoundBuffer(m_resources->getWhipSound());
	newMelee->playSound();
	attack(newMelee);
}

//----------------------------------------------------------
void Player::updgradeWhip()
{
	if (m_whipLevel < 3)
		m_whipLevel++;
}

//----------------------------------------------------------
void Player::setWeapon(int newWeapon)
{
	m_weaponHeld = newWeapon;
	switch (newWeapon)
	{
		case 0:
		{
			m_currentSubweapon = m_emptyTexture;
			m_subweaponTextureSize = { 5,5 };
			break;
		}
		case 1:
		{
			Dagger tempDagger;
			m_currentSubweapon = m_daggerTexture;
			m_subweaponTextureSize = tempDagger.getWeaponSize();
			break;
		}
		case 2:
		{
			Axe tempAxe;
			m_currentSubweapon = m_axeTexture;
			m_subweaponTextureSize = tempAxe.getWeaponSize();
			break;
		}
		case 3:
		{
			Boomerang tempBoomerang;
			m_currentSubweapon = m_boomerangTexture;
			m_subweaponTextureSize = tempBoomerang.getWeaponSize();
			break;
		}
	}
}

//----------------------------------------------------------
sf::Vector2f Player::getWhipSize()
{
	if (m_whipLevel != 3 )
		return sf::Vector2f(28, 9);
	else
		return sf::Vector2f(44, 9);
}

//----------------------------------------------------------
void Player::setClimbing(sf::Vector2f startLocation, int numOfStairs, DIRECTION direction, int elevation)
{
	float x, y;
	defaultState();
	m_climbing = true;
	m_stairsElevation = elevation;
	m_totalStairs = numOfStairs + 1;
	move(direction);
	//If climbing down
	if (elevation == 1)
	{
		y = getHitbox().getGlobalBounds().top;
		if (direction == LEFT)
			x = startLocation.x - 8;
		else
			x = startLocation.x;
	}
	//If climbing up
	else
	{
		y = getHitbox().getGlobalBounds().top + 8;
		if (direction == RIGHT)
			x = startLocation.x - 8;
		else
			x = startLocation.x;
	}
	if (m_crouching)
		m_crouching = false;
	setPosition({ x,y });
	m_sprite.setTextureRect(sf::IntRect(0, 256, SPRITE_WIDTH, SPRITE_HEIGHT));
}

//----------------------------------------------------------
void Player::climbStairs()
{
	float x, y;
	static int counter = 0;
	int counterLimit = 10;

	//Finish climbing stairs
	if (m_totalStairs == m_currentStair)
	{
		m_climbing = false;
		m_stairStanding = false;
		defaultState();
		m_currentStair = 0;
		return;
	}


	//When reached a step
	if (counter >= counterLimit)
	{
		m_currentStair++;
		m_velocity = { 0,0 };
		m_sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH, m_stairsElevation == 1 ? 256 : 288, SPRITE_WIDTH, SPRITE_HEIGHT));
		m_stairStanding = true;
		counter = 0;
		return;
	}
	if (m_stairStanding && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_velocity = { 0,0 };
		return;
	}
	//If trying to change direction while climbing the stairs
	else if (m_stairStanding && ( (m_stairsElevation == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || (m_stairsElevation == 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ||
		(m_direction == RIGHT && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (m_direction == LEFT && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ) )
	{
		if (m_direction == LEFT)
			move(RIGHT);
		else
			move(LEFT);
		m_currentStair = m_totalStairs - m_currentStair;
		if (m_stairsElevation == 1)
			m_stairsElevation = 0;
		else
			m_stairsElevation = 1;
	}
	if (m_isAttacking)
		return;
	m_stairStanding = false;
	//Adjust animation and stair movement
	if (counter <= counterLimit / 2)
		m_sprite.setTextureRect(sf::IntRect(0, 288, SPRITE_WIDTH, SPRITE_HEIGHT));
	else
		m_sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH, m_stairsElevation == 1 ? 256 : 288, SPRITE_WIDTH, SPRITE_HEIGHT));

	if (m_stairsElevation == 1)
		y = float(8) / counterLimit;
	else
		y = float(-8) / counterLimit;
	if (m_direction == RIGHT)
		x = float(8) / counterLimit;
	else
		x = float(-8) / counterLimit;
	m_velocity = { x, y };
	counter++;
	if (m_stairsElevation == 1 && m_currentStair == m_totalStairs - 1)
	{
		m_velocity = { 0,0 };
		counter++;
	}
}

//----------------------------------------------------------
void Player::jump()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_moveBeforeJumping = true;
	m_sprite.setTextureRect({ SPRITE_WIDTH * 3, 0, SPRITE_WIDTH, SPRITE_HEIGHT });
	m_hitbox.setSize(sf::Vector2f(HITBOX_WIDTH, CROUCHING_HEIGHT));
	m_sprite.move(sf::Vector2f(0, -abs(SPRITE_HEIGHT - CROUCHING_HEIGHT)));
	Character::jump();
}

//----------------------------------------------------------
void Player::die()
{
	if (!m_deathAnimation)
	{
		m_animationDelay = 0;
		m_animationStage = 0;
		m_deathAnimation = true;
	}
		loopingAnimation(2, SPRITE_WIDTH, SPRITE_HEIGHT, SPRITE_HEIGHT * 16);
	if (m_animationDelay == ANIMATION_DELAY && m_animationStage == 2)
	{
		defaultState();
		m_animationDelay = 0;
		m_animationStage = 0;
		setRemoveFlag(true);
		m_deathAnimation = false;
		m_velocity = { 0,0 };
		m_lives--;
	}
	m_climbing = false;
	m_stairStanding = false;
	m_currentStair = 0;
}

//----------------------------------------------------------
void Player::update(std::vector<sf::RectangleShape>& rect)
{
	//Disable damage animation after landing, or die if ran out of health
	if (m_isDamaged && !m_falling || m_remainingTime <= 0)
		if (m_midRemoval || m_remainingTime <= 0)
		{
			die();
			return;
		}
		else
			m_isDamaged = false;

	//Enable changing direction right after landing
	if (!m_falling)
	{
		m_moveBeforeJumping = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			getButtonPress(sf::Keyboard::Left);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			getButtonPress(sf::Keyboard::Right);
	}
	//Disable crouch state
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !m_isAttacking && m_crouching || (m_velocity.y > 0 && !m_isAttacking))
	{
		defaultState();
		setCrouch(false);
	}

	//Disable gravity while climbing the stairs
	if (m_climbing)
		m_velocity.y = 0;

	//Move the character in the desired direction
	if ((!m_falling && (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) || 
		(m_falling && m_moveBeforeJumping && !getHorizontalCollision()))
		switch (m_direction)
		{
		case LEFT:
			m_velocity.x = -m_movementSpeed;
			break;
		case RIGHT:
			m_velocity.x = m_movementSpeed;
			break;
		}

	environmentCollisions(rect);

	//Stop moving after a jump if no direction is pressed, or if crouching or attacking
	if (!m_falling && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (m_crouching && !m_isDamaged) || (m_isAttacking && !m_falling) || (m_isThrowing && !m_isDamaged && !m_falling) || getHorizontalCollision())
		m_velocity.x = 0;

	//Make the player invincible for a short while after getting hit
	if (m_isInvincible)
	{
		if (m_invincibilityDelay < ANIMATION_DELAY)
			m_invincibilityDelay++;
		else
		{
			if (m_sprite.getColor() != sf::Color::Transparent)
				m_sprite.setColor(sf::Color::Transparent);
			else
				m_sprite.setColor(sf::Color::White);
			m_invincibilityDelay = 0;
		}
	}

	//Disable invincibility
	if (m_invincibilityTimer.getElapsedTime() > sf::seconds(INVINCIBILITY_TIME))
	{
		m_sprite.setColor(sf::Color::White);
		m_invincibilityDelay = 0;
		m_isInvincible = false;
	}

	if (m_climbing)
		climbStairs();

	//Count down level timer and die if ran out of time
	m_remainingTime = m_remainingTime - m_levelTime.getElapsedTime().asSeconds();
	if (m_remainingTime <= 0)
		m_midRemoval = true;
	m_levelTime.restart();

		animate();
	Character::update();
}

//----------------------------------------------------------
void Player::animate()
{
	//Damage animation
	if (m_isDamaged && m_falling) 
	{
		m_sprite.setTextureRect({ SPRITE_WIDTH * 4, 0, SPRITE_WIDTH, SPRITE_HEIGHT });
		m_isThrowing = false;
		m_crouching = false;
		if (m_isAttacking)
		{
			m_isAttacking = false;
			if (m_attacks.size() != 0 && m_attacks[m_attacks.size() - 1] != nullptr)
			{
			m_attacks.pop_back();
			}
		}
		return;
	}
	if (!m_crouching && !m_isAttacking && m_velocity.x == 0 && !m_isThrowing && !m_climbing && !m_stairStanding && !m_falling)
		defaultState();
	if (m_isAttacking)
	{
		animateWhip();
	}
	if (m_crouching && !m_isAttacking)
	{
		m_sprite.setTextureRect({ SPRITE_WIDTH * 3, 0, SPRITE_WIDTH, SPRITE_HEIGHT });
		m_hitbox.setSize(sf::Vector2f(HITBOX_WIDTH, CROUCHING_HEIGHT));
		if (m_direction == RIGHT)
			m_hitbox.setPosition(m_sprite.getGlobalBounds().left, m_sprite.getGlobalBounds().top + 8);
		else
			m_hitbox.setPosition(m_sprite.getGlobalBounds().left + m_sprite.getGlobalBounds().width - HITBOX_WIDTH, m_sprite.getGlobalBounds().top + 8);
	}
	else if (m_velocity.x != 0 && !m_falling && (!m_climbing)) //Walking animation
	{
		rewindingAnimation(WALKING_FRAMES, SPRITE_WIDTH, SPRITE_HEIGHT, 0);
		if (m_animationStage == -1 && m_animationDirection == LEFT)
			m_animationDirection = RIGHT;
	}
	if (m_isThrowing)
	{
		throwWeapon();
	}
}

//----------------------------------------------------------
void Player::animateWhip()
{
	if (!m_crouching && !m_stairStanding)
		rewindingAnimation(ATTACKING_FRAMES, SPRITE_WIDTH, SPRITE_HEIGHT, 64 + ((m_whipLevel - 1) * SPRITE_HEIGHT));
	else if (m_stairStanding)
		if (m_stairsElevation == 1)
		rewindingAnimation(ATTACKING_FRAMES, SPRITE_WIDTH, SPRITE_HEIGHT, 320 + ((m_whipLevel - 1) * SPRITE_HEIGHT));
		else
			rewindingAnimation(ATTACKING_FRAMES, SPRITE_WIDTH, SPRITE_HEIGHT, 416 + ((m_whipLevel - 1) * SPRITE_HEIGHT));
	else
		rewindingAnimation(ATTACKING_FRAMES, SPRITE_WIDTH, SPRITE_HEIGHT, 160 + ((m_whipLevel - 1) * SPRITE_HEIGHT));
	if (m_animationStage == ATTACKING_FRAMES && m_animationDelay == 0 && m_animationDirection == LEFT)
		useWhip();
	else if (m_animationStage == ATTACKING_FRAMES && m_animationDelay == ANIMATION_DELAY && m_animationDirection == LEFT)
	{
		m_attacks.pop_back();
		m_isAttacking = false;
		if (!m_stairStanding)
			defaultState();
		else
			m_sprite.setTextureRect(sf::IntRect(SPRITE_WIDTH, m_stairsElevation == 1 ? 256 : 288, SPRITE_WIDTH, SPRITE_HEIGHT));
	}
}

//----------------------------------------------------------
void Player::throwWeapon()
{
	rewindingAnimation(ATTACKING_FRAMES, SPRITE_WIDTH, SPRITE_HEIGHT, SPRITE_HEIGHT);
	if (m_animationStage == ATTACKING_FRAMES && m_animationDelay == ANIMATION_DELAY && m_animationDirection == LEFT)
	{
		if (m_weaponHeld == 1)
		{
			std::shared_ptr<Dagger> newDagger = std::make_shared<Dagger>(m_sprite.getPosition(), m_direction);
			newDagger->setTexture(m_daggerTexture);
			newDagger->setSoundBuffer(m_resources->getThrowWeaponSound());
			newDagger->playSound();
			attack(newDagger);
		}
		else if (m_weaponHeld == 2)
		{
			std::shared_ptr<Axe> newAxe = std::make_shared<Axe>(m_sprite.getPosition(), m_direction);
			newAxe->setTexture(m_axeTexture);
			newAxe->setSoundBuffer(m_resources->getThrowWeaponSound());
			newAxe->playSound();
			attack(newAxe);
		}
		else if (m_weaponHeld == 3)
		{
			std::shared_ptr<Boomerang> newBoomerang = std::make_shared<Boomerang>(m_sprite.getPosition(), m_direction);
			newBoomerang->setTexture(m_boomerangTexture);
			newBoomerang->setSoundBuffer(m_resources->getBoomerangSound());
			attack(newBoomerang);
		}
		m_hearts--;
		m_isThrowing = false;
		defaultState();
	}

}

//----------------------------------------------------------
void Player::collectItem(int itemType)
{
	switch (itemType)
	{
		case 0:
			m_health = MAX_HEALTH;
			break;
		case 1:
			m_hearts++;
			if (m_hearts > 99)
				m_hearts = 99;
			break;
		case 2:
			m_hearts += 5;
			if (m_hearts > 99)
				m_hearts = 99;
			break;
	}
}

//----------------------------------------------------------
void Player::checkAttackTarget(std::weak_ptr<Object> obj)
{
	std::shared_ptr<Object> objPTR = obj.lock();
	if (obj.expired())
		return;
	for (auto i : m_attacks)
		if (i->collision(obj))
		{
			for (auto k : i->getAffectedCharacters()) //Check if the same object has already been hit by the same weapon instance
				if (objPTR == k)
					return;
			//
			if (std::dynamic_pointer_cast<Character>(objPTR))
			{
				std::dynamic_pointer_cast<Character>(objPTR)->getHit(shared_from_this());
				if (objPTR->getRemovalFlagState())
					addScore(std::dynamic_pointer_cast<Enemy>(objPTR)->getPoints());
			}
			else
				objPTR->getHit(std::dynamic_pointer_cast<Object>(Player::shared_from_this()));
			objPTR->playSound();
			//Add object to list of objects that have been already hit by that weapon
			i->addCharacterHit(obj);
			break;
		}
}

//----------------------------------------------------------
void Player::getHit(std::weak_ptr<Character> hitChar)
{
	if (m_isInvincible)
		return;
	playSound();
	m_health -= hitChar.lock()->getStrength();
	m_isInvincible = true;
	m_invincibilityTimer.restart();

	//Fall to the left or right depending on the direction currently facing
	if (!m_climbing && !m_stairStanding)
	{
		m_velocity.x = m_direction == LEFT ? 2.2 : -2.2;
		m_velocity.y = -2.5;
		m_falling = true;
	}
	m_isDamaged = true;
	if (m_health <= 0)
		m_midRemoval = true;
}

//----------------------------------------------------------
void Player::draw(sf::RenderWindow& window)
{
	//Adjust sprite location based on current animation frame
	if (m_isAttacking && m_stairStanding)
	{
		if (m_animationStage == 1)
		{
			m_sprite.move(sf::Vector2f(m_direction == RIGHT ? -16 : 16, 0));
			Character::draw(window);
			m_sprite.move(sf::Vector2f(m_direction == RIGHT ? 16 : -16, 0));
		}
		else if (m_animationStage == 2)
		{
			m_sprite.move(sf::Vector2f(m_direction == RIGHT ? -16 : 16, 0));
			Character::draw(window);
			m_sprite.move(sf::Vector2f(m_direction == RIGHT ? 16 : -16, 0));
		}
		else
			Character::draw(window);
	}
	else if (m_isAttacking && !m_stairStanding)
	{
		if (m_animationStage == 1)
		{
			m_sprite.move(sf::Vector2f(m_direction == RIGHT ? -16 : 16, !m_crouching ? 1 : 8));
			Character::draw(window);
			m_sprite.move(sf::Vector2f(m_direction == RIGHT ? 16 : -16, !m_crouching ? -1 : -8));
		}
		else if (m_animationStage == 2 && m_animationDirection == RIGHT)
		{
			m_sprite.move(sf::Vector2f(m_direction == RIGHT ? -16 : 16, 0));
			Character::draw(window);
			m_sprite.move(sf::Vector2f(m_direction == RIGHT ? 16 : -16, 0));
		}
		else
			Character::draw(window);
	}
	else if (m_isThrowing)
	{
		if (m_animationStage == 1)
		{
			m_sprite.move(sf::Vector2f(m_direction == RIGHT ? -8 : 8, 0));
			Character::draw(window);
			m_sprite.move(sf::Vector2f(m_direction == RIGHT ? 8 : -8, 0));
		}
		else
			Character::draw(window);
	}
	else
		Character::draw(window);
}

//----------------------------------------------------------
void Player::automatedMovement(DIRECTION direction)
{
	move(direction);
	m_velocity.x = direction == 0 ? -MOVEMENT_SPEED : MOVEMENT_SPEED;
	animate();
	Mobile::update();
}

//----------------------------------------------------------
void Player::resetTimer()
{
	m_remainingTime = LEVEL_TIME;
	m_levelTime.restart();
}
