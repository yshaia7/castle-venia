#include "Boomerang.h"


//----------------------------------------------------------
Boomerang::Boomerang(sf::Vector2f origin, int direction) : Range(origin, direction)
{
	setVolume(50);
	m_returning = false;
	m_velocity.x = SPEED;
	m_returningSpeed = -0.05;
	if (direction == 0)
	{
		m_returningSpeed = -m_returningSpeed;
		m_velocity.x = -m_velocity.x;
	}
	m_soundTimer.restart();
	m_sprite.setTextureRect({ 0, 0, SPRITE_WIDTH, SPRITE_HEIGHT });
}

//----------------------------------------------------------
Boomerang::~Boomerang()
{
}

//----------------------------------------------------------
void Boomerang::update()
{
	m_velocity.x += m_returningSpeed;
	if (m_soundTimer.getElapsedTime() > sf::seconds(0.2))
	{
		playSound();
		m_soundTimer.restart();
	}
	if (!m_returning && ((m_direction == 0 && m_velocity.x > 0) || (m_direction == 1 && m_velocity.x < 0)))
	{
		m_returning = true;
		m_characters.clear();
	}
	if ((m_direction == 0 && m_velocity.x < -SPEED) || (m_direction == 1 && m_velocity.x > SPEED))
		m_velocity.x = m_direction == 0 ? -SPEED : SPEED;
	loopingAnimation(NUM_OF_FRAMES, SPRITE_WIDTH, SPRITE_HEIGHT, 0);
	Weapon::update();

}
