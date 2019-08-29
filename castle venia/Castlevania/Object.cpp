#include "Object.h"


//----------------------------------------------------------
Object::Object()
{
	setActive(true);
	m_removeFlag = false;
	m_midRemoval = false;
	m_animationStage = 0;
	m_animationDelay = 0;
}

//----------------------------------------------------------
Object::~Object()
{
}

//----------------------------------------------------------
void Object::draw(sf::RenderWindow& window)
{
	if (m_isActive)
		window.draw(m_sprite);
}

//----------------------------------------------------------
void Object::setTexture(sf::Texture & texture)
{
	m_sprite.setTexture(texture);
	m_hitbox.setSize({ m_sprite.getGlobalBounds().width,m_sprite.getGlobalBounds().height });
}

//----------------------------------------------------------
void Object::setActive(bool activeState)
{
	m_isActive = activeState;
}

//----------------------------------------------------------
void Object::setPosition(sf::Vector2f newPos)
{
	m_sprite.setPosition(newPos);
	m_hitbox.setPosition(newPos);
}

//----------------------------------------------------------
void Object::loopingAnimation(int numOfFrames, int spriteWidth, int spriteHeight, int spriteY)
{
	if (m_animationDelay != ANIMATION_DELAY)
	{
		m_animationDelay++;
		return;
	}
	if (m_animationDelay == ANIMATION_DELAY && m_animationStage == numOfFrames)
		m_animationStage = 0;
	m_animationDelay = 0;
	m_sprite.setTextureRect({ spriteWidth * m_animationStage, spriteY, spriteWidth, spriteHeight });
	m_animationStage++;
}
