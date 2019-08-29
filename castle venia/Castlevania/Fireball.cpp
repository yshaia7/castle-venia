#include "Fireball.h"


//----------------------------------------------------------
Fireball::Fireball(sf::Vector2f origin, int direction) : Range(origin, direction)
{
	m_velocity.x = 3;
	if (direction == 0)
	{
		m_velocity.x = -m_velocity.x;
		m_sprite.setOrigin({ m_sprite.getLocalBounds().left, 0 });
		m_sprite.scale(-1, 1);
	}
}

//----------------------------------------------------------
Fireball::~Fireball()
{
}
