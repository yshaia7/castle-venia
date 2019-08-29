#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Immobile.h"

//- - - - - - - - - - - - #define sectoin - - - - - - 
#define SPRITE_WIDTH 16
#define SPRITE_HEIGHT 33

class Block : public Immobile
{
public:
	Block(sf::Vector2f location, ResourceManager& rManager);
	~Block();
	void destroy();
	void setActive(bool activeState);
private:
	bool m_crumbling; //Reaches this state after being hit once
};

