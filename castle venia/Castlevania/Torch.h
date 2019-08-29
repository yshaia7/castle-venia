#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Immobile.h"

//- - - - - - - - - - - - #define sectoin - - - - - - 
#define SPRITE_WIDTH 16
#define SPRITE_HEIGHT 32
#define NUM_OF_FRAMES 2

class Torch : public Immobile
{
public:
	Torch(sf::Vector2f location, int type, ResourceManager& rManager);
	~Torch();
	void playerInteraction(std::weak_ptr<Player> player, std::vector<sf::RectangleShape>& rect);
}; 

