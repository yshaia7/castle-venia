#include "Stairs.h"


//----------------------------------------------------------
Stairs::Stairs(sf::Vector2f startPoint, int numOfStairs, int direction, int elevation) : m_numOfStairs(numOfStairs), m_direction(direction == 0 ? LEFT : RIGHT), m_elevation(elevation)
{
	if (m_elevation == 1)
		if (m_direction == RIGHT)
			startPoint.x -= STAIRS_LENGTH * 2;
		else
			startPoint.x += STAIRS_LENGTH;
	else
		if (m_direction == RIGHT)
			startPoint.x -= STAIRS_LENGTH;
	if (m_elevation == 0)
		startPoint.y += 8;
	else
		startPoint.y -= STAIRS_HEIGHT;
	m_location = startPoint;
	m_hitbox.setPosition(m_location);
	m_hitbox.setSize(sf::Vector2f(STAIRS_LENGTH, STAIRS_HEIGHT));
}

//----------------------------------------------------------
Stairs::~Stairs()
{
}

//----------------------------------------------------------
void Stairs::playerInteraction(std::weak_ptr<Player> player)
{
	std::shared_ptr<Player> playerPTR = player.lock();
	if (playerPTR->checkInaction() && ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_elevation == 0) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_elevation == 1)) &&
		abs(playerPTR->getHitbox().getGlobalBounds().top + playerPTR->getHitbox().getGlobalBounds().height - m_hitbox.getGlobalBounds().top < 6) && collision(player))
	{
		playerPTR->setClimbing(m_location, m_numOfStairs, m_direction, m_elevation);
	}
}
