#include "Mobile.h"


//----------------------------------------------------------
Mobile::Mobile()
{
	m_velocity = { 0,0 };
	m_falling = false;
	m_horizontalCollision = false;
}

//----------------------------------------------------------
Mobile::~Mobile()
{
}

//----------------------------------------------------------
bool Mobile::verticalCollision(sf::RectangleShape& rect)
{
	sf::RectangleShape tempSprite(m_hitbox);
	tempSprite.move({ 0, m_velocity.y });

	if (m_velocity.y > 0 && tempSprite.getGlobalBounds().intersects(rect.getGlobalBounds()) && m_hitbox.getGlobalBounds().top + m_hitbox.getGlobalBounds().height <= rect.getGlobalBounds().top)
		return true;
	return false;
}

//----------------------------------------------------------
bool Mobile::horizontalCollision(sf::RectangleShape& rect)
{
	sf::RectangleShape tempSprite(m_hitbox);
	tempSprite.move({ m_velocity.x, 0 });
	if (!m_horizontalCollision && tempSprite.getGlobalBounds().intersects(rect.getGlobalBounds()))
	{
		m_horizontalCollision = true;
		return true;
	}
	m_horizontalCollision = false;
	return false;
}

//----------------------------------------------------------
void Mobile::environmentCollisions(std::vector<sf::RectangleShape>& rect)
{
	setGravity();
	//Check if falling on an object
	for (auto i : rect)
		if (verticalCollision(i))
		{
			m_falling = false;
			m_velocity.y = 0;
			break;
		}
	//Check if about to collide with an object to the left or right
	for (auto i : rect)
		if (horizontalCollision(i))
		{
			m_velocity.x = 0;
			break;
		}
}

//----------------------------------------------------------
void Mobile::update()
{
	m_sprite.move(m_velocity);
	m_hitbox.move(m_velocity);
}

//----------------------------------------------------------
void Mobile::setGravity()
{
	m_falling = true;
	m_velocity.y += GRAVITY;
}