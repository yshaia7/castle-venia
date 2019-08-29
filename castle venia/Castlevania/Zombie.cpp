#include "Zombie.h"

//----------------------------------------------------------
Zombie::Zombie(sf::Vector2f startLocation, ResourceManager & rManager) : Enemy(startLocation, rManager)
{
	setTexture(rManager);
	m_health = 2;
	m_strength = 2;
	m_spawnDistanceMin = 150;
	m_spawnDistanceMax = 300;
	setMaxHealth(MAX_HEALTH);
	m_points = 100;
}

//----------------------------------------------------------
Zombie::~Zombie()
{
}

//----------------------------------------------------------
void Zombie::playerInteraction(std::weak_ptr<Player> player)
{
	Enemy::playerInteraction(player);
}

//----------------------------------------------------------
void Zombie::update()
{
	if (!getRemovalFlagState())
	{
		move(m_direction);
		m_velocity.x = m_direction == RIGHT ? MOVEMENT_SPEED : -MOVEMENT_SPEED;
		rewindingAnimation(WALKING_FRAMES, SPRITE_WIDTH, SPRITE_HEIGHT, 0);
	}
	Character::update();
}

//----------------------------------------------------------
void Zombie::setTexture(ResourceManager & rManager)
{
	Object::setTexture(rManager.getZombieTexture());
	m_sprite.setTextureRect({ 0,0, SPRITE_WIDTH, SPRITE_HEIGHT });
	m_hitbox.setSize(sf::Vector2f(m_sprite.getTextureRect().width, m_sprite.getTextureRect().height));
}

