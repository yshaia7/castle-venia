#include "SmallHeart.h"


//----------------------------------------------------------
SmallHeart::SmallHeart(sf::Vector2f location, ResourceManager& rManager) : Item(location, rManager)
{
	setSoundBuffer(rManager.getCollectHeartSound());
	setTexture(rManager.getSHeartTexture());
	m_flightArc = 0;
	m_falling = true;
}

//----------------------------------------------------------
SmallHeart::~SmallHeart()
{
}

//----------------------------------------------------------
void SmallHeart::playerInteraction(std::weak_ptr<Player> player, std::vector<sf::RectangleShape>& rect)
{
	if (m_falling)
		m_velocity.x = cos((float)++m_flightArc / FLIGHT_ARC_LIMITER);
	for (auto i : rect)
		if (verticalCollision(i))
		{
			m_falling = false;
			m_velocity.x = 0;
			break;
		}
	if (m_velocity.y > 0.2)
		m_velocity.y = 0.2;
	Item::playerInteraction(player, rect);
}
