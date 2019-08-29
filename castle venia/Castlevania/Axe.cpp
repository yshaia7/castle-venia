#include "Axe.h"


//----------------------------------------------------------
Axe::Axe(sf::Vector2f origin, int direction) : Range(origin, direction) 
{
	m_velocity.x = 2;
	m_velocity.y = -7;
	if (direction == 0)
		m_velocity.x = -m_velocity.x;
	m_sprite.setTextureRect({ 0,0,SPRITE_WIDTH,SPRITE_HEIGHT });
	m_animationDelay = 4;
}

//----------------------------------------------------------
Axe::~Axe()
{

}

//----------------------------------------------------------
void Axe::update()
{
	setGravity();
	loopingAnimation(NUM_OF_FRAMES, SPRITE_WIDTH, SPRITE_HEIGHT, 0);
	Mobile::update();
}