#include "Dagger.h"


//----------------------------------------------------------
Dagger::Dagger(sf::Vector2f origin, int direction) : Range(origin, direction)
{
	m_velocity.x = 5;
	if (direction == 0)
	{
		m_velocity.x = -m_velocity.x;
		m_sprite.setOrigin({ m_sprite.getLocalBounds().left, 0 });
		m_sprite.scale(-1, 1);
	}
}

//----------------------------------------------------------
Dagger::~Dagger()
{
}

//----------------------------------------------------------
void Dagger::update()
{
	if (m_characters.size() > 0)
		destroy();
	Weapon::update();
}
