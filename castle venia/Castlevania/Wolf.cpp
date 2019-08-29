#include "Wolf.h"

//----------------------------------------------------------
Wolf::Wolf(sf::Vector2f startLocation, ResourceManager& rManager) : Enemy(startLocation, rManager)
{
	setTexture(rManager);
	m_health = 2;
	m_strength = 2;
	m_points = 200;
	m_spawnDistanceMin = 200;
	m_spawnDistanceMax = 300;
	m_isAwake = false;
	m_landed = false;
	m_jumpingHeight = JUMPING_HEIGHT;
	m_movementSpeed = MOVEMENT_SPEED;
	setMaxHealth(MAX_HEALTH);
}

//----------------------------------------------------------
Wolf::~Wolf()
{
}

//----------------------------------------------------------
void Wolf::playerInteraction(std::weak_ptr<Player> player)
{
	Enemy::playerInteraction(player);
	std::shared_ptr<Player> playerPTR = player.lock();

	if (!getRemovalFlagState() || getActive())
	{
		if (!m_isAwake && abs(playerPTR->getLocation().x - m_hitbox.getGlobalBounds().left) <= AWAKENING_DISTANCE)
		{
			m_isAwake = true;
			move(playerPTR->getLocation().x > m_hitbox.getGlobalBounds().left ? RIGHT : LEFT);
			jump();
		}

		//Turn to the player one time after landing
		if (!m_falling && m_isAwake && !m_landed)
		{
			m_landed = true;
			move(playerPTR->getLocation().x > m_hitbox.getGlobalBounds().left ? RIGHT : LEFT);
		}
	}
}

//----------------------------------------------------------
void Wolf::spawnEnemy()
{
	m_isAwake = false;
	m_landed = false;
	m_sprite.setTextureRect({ SPRITE_WIDTH * 3 ,0, SPRITE_WIDTH, SPRITE_HEIGHT });
	Enemy::spawnEnemy();
}

//----------------------------------------------------------
void Wolf::update()
{
	if (!getRemovalFlagState())
	{
		if (m_isAwake)
		{
			move(m_direction);
			m_velocity.x = m_direction == RIGHT ? MOVEMENT_SPEED : -MOVEMENT_SPEED;
			rewindingAnimation(WALKING_FRAMES, SPRITE_WIDTH, SPRITE_HEIGHT, 0);
		}
		else
			m_velocity.x = 0;
	}

	Character::update();
}

//----------------------------------------------------------
void Wolf::setTexture(ResourceManager & rManager)
{
	Object::setTexture(rManager.getWolfTexture());
	m_sprite.setTextureRect({ SPRITE_WIDTH * 3 ,0, SPRITE_WIDTH, SPRITE_HEIGHT });
	m_hitbox.setSize(sf::Vector2f(m_sprite.getTextureRect().width, m_sprite.getTextureRect().height));
}

