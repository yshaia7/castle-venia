#include "Pit.h"


//----------------------------------------------------------
Pit::Pit(sf::Vector2f size, sf::Vector2f position)
{
	m_hitbox.setSize(size);
	m_hitbox.setPosition(position);
}

//----------------------------------------------------------
Pit::~Pit()
{
}
//----------------------------------------------------------
void Pit::playerInteraction(std::weak_ptr<Player> player, std::vector<sf::RectangleShape>& rect)
{
	std::shared_ptr<Player> playerPTR = player.lock();
	if (playerPTR->getHitbox().getPosition().y > m_hitbox.getPosition().y)
		playerPTR->die();
}
