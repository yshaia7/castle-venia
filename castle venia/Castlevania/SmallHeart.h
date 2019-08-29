#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Item.h"

//- - - - - - - - - - - - define sectoin - - - - - - 
#define FLIGHT_ARC_LIMITER 10

class SmallHeart : public Item
{
public:
	SmallHeart(sf::Vector2f location, ResourceManager& rManager);
	~SmallHeart();
	void playerInteraction(std::weak_ptr<Player> player, std::vector<sf::RectangleShape>& rect);

protected:
	void useItemEffect(std::weak_ptr<Player> player) { player.lock()->addHearts(1); }
	int m_flightArc;
	bool m_falling;
};

