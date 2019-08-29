#include "Merman.h"

//----------------------------------------------------------
Merman::Merman(sf::Vector2f startLocation, ResourceManager & rManager) : Enemy(startLocation, rManager)
{

	setTexture(rManager);

	m_strength = 2;
	m_spawnDistanceMin = 10;
	m_spawnDistanceMax = 200;
	m_hasJumped = false;
	m_jumpingHeight = JUMPING_HEIGHT;
	m_movementSpeed = MOVEMENT_SPEED;
	setMaxHealth(MAX_HEALTH);
	m_fireballTexture = rManager.getFireballTexture();
	m_respawnTimer.restart();
	m_nextRespawnTime = 0;
	m_points = 250;
}

//----------------------------------------------------------
void Merman::playerInteraction(std::weak_ptr<Player> player)
{
	Enemy::playerInteraction(player);
	if (!getActive())
	{
		m_hasJumped = false;
		return;
	}
	if (!m_hasJumped)
	{
		m_falling = false;
		jump();
		m_hasJumped = true;
	}

}

//----------------------------------------------------------
void Merman::spawnEnemy()
{
	if (m_respawnTimer.getElapsedTime() >= sf::seconds(m_nextRespawnTime))
	{
		int spawnOffset;
		m_hasJumped = false;
		m_shootTimerActive = false;
		m_isShooting = false;
		m_fireDelay = 0;
		m_sprite.setTextureRect({ 0,0, SPRITE_WIDTH, SPRITE_HEIGHT });
		Enemy::spawnEnemy();
		spawnOffset = rand() % RESPAWN_RANGE - RESPAWN_RANGE / 2;
		setPosition({ m_hitbox.getPosition().x + spawnOffset, m_hitbox.getPosition().y });
		m_nextRespawnTime = rand() % 5 + 1;
		
	}
}

//----------------------------------------------------------
void Merman::update()
{
	if (!getRemovalFlagState())
	{
		move(m_direction);
		if (!m_falling)
		{
			if (!m_shootTimerActive)
			{
				m_shootTimerActive = true;
				m_shootTimer.restart();
				m_timeUntilShooting = rand() % 3 + 0.5;
			}
			else if (m_isShooting || (m_shootTimer.getElapsedTime() >= sf::seconds(m_timeUntilShooting) && m_attacks.size() == 0))
			{
				m_isShooting = true;
				shootFireball();
			}
			else
			{
				m_velocity.x = m_direction == RIGHT ? MOVEMENT_SPEED : -MOVEMENT_SPEED;
				rewindingAnimation(WALKING_FRAMES, SPRITE_WIDTH, SPRITE_HEIGHT, 0);
			}
		}
		else
			m_velocity.x = 0;
	}
	Enemy::update();
}

//----------------------------------------------------------
void Merman::setTexture(ResourceManager & rManager)
{
	Object::setTexture(rManager.getMermanTexture());
	m_sprite.setTexture(rManager.getMermanTexture());
	m_sprite.setTextureRect({ 0,0, SPRITE_WIDTH, SPRITE_HEIGHT });
	m_hitbox.setSize(sf::Vector2f(m_sprite.getTextureRect().width, m_sprite.getTextureRect().height));
}

//----------------------------------------------------------
void Merman::shootFireball()
{
	m_velocity.x = 0;
	m_sprite.setTextureRect({ SPRITE_WIDTH * 2, 0, SPRITE_WIDTH, SPRITE_HEIGHT });
	if (m_fireDelay < FIRE_DELAY - 5)
	{
		m_fireDelay++;
		return;
	}
	if (m_attacks.size() == 0)
	{
		std::shared_ptr<Fireball>newFireball;
		newFireball = std::make_shared<Fireball>(sf::Vector2f(m_hitbox.getPosition().x, m_hitbox.getPosition().y + 2), m_direction);
		attack(newFireball);
		m_attacks[0]->setTexture(m_fireballTexture);
	}
	if (m_fireDelay < FIRE_DELAY)
	{
		m_fireDelay++;
		return;
	}
	m_shootTimer.restart();
	m_fireDelay = 0;
	move(m_direction == LEFT ? RIGHT : LEFT);
	m_isShooting = false;
}

//----------------------------------------------------------
void Merman::destroy()
{
	m_respawnTimer.restart();
	Object::destroy();
}