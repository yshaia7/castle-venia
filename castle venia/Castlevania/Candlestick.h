#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Immobile.h"

//- - - - - - - - - - - - #define sectoin - - - - - - 
#define SPRITE_WIDTH 8
#define SPRITE_HEIGHT 16
#define NUM_OF_FRAMES 2

class Candlestick : public Immobile
{
public:
	Candlestick(sf::Vector2f location, int type, ResourceManager& rManager);
	~Candlestick();
	void playerInteraction(std::weak_ptr<Player> player, std::vector<sf::RectangleShape>& rect);
};

