#pragma once 
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Immobile.h"

class Pit : public Immobile
{
public:
	Pit(sf::Vector2f size, sf::Vector2f position);
	~Pit();
	void playerInteraction(std::weak_ptr<Player> player, std::vector<sf::RectangleShape>& rect);
};

