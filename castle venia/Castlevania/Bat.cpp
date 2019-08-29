#include "Bat.h"
#include <cmath>
#include <string.h>

//----------------------------------------------------------
Bat::Bat(sf::Vector2f startLocation, ResourceManager & rManager) : Enemy(startLocation, rManager)
{
	setTexture(rManager);
	m_health = 2;
	m_strength = 5;
	m_spawnDistanceMin = 200;
	m_spawnDistanceMax = 300;
	setMaxHealth(MAX_HEALTH);
	m_flightArcCounter = 0;
	m_points = 100;
}

//----------------------------------------------------------
Bat::~Bat()
{
}

//----------------------------------------------------------
void Bat::update()
{
	if (!getRemovalFlagState())
	{
		move(m_direction);
		m_velocity.x = m_direction == RIGHT ? MOVEMENT_SPEED : -MOVEMENT_SPEED;

		m_velocity.y = cos((float)++m_flightArcCounter / FLIGHT_ARC_LIMITER);

		rewindingAnimation(WALKING_FRAMES, SPRITE_WIDTH, SPRITE_HEIGHT, 0);
	}
	Character::update();
}

//----------------------------------------------------------
void Bat::setTexture(ResourceManager & rManager)
{
	Object::setTexture(rManager.getBatTexture());
	m_sprite.setTextureRect({ 0,0, SPRITE_WIDTH, SPRITE_HEIGHT });
	m_hitbox.setSize(sf::Vector2f(m_sprite.getTextureRect().width, m_sprite.getTextureRect().height));
}

