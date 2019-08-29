#include "Block.h"

//----------------------------------------------------------
Block::Block(sf::Vector2f location, ResourceManager& rManager) : Immobile(location, 1, rManager)
{
	setTexture(rManager.getBlockTexture());
	m_sprite.setTextureRect({ 0, 0, SPRITE_WIDTH, SPRITE_HEIGHT });
	m_crumbling = false;
}

//----------------------------------------------------------
Block::~Block()
{
}

//----------------------------------------------------------
void Block::destroy()
{
	if (!m_crumbling)
	{
		m_crumbling = true;
		m_sprite.setTextureRect({ SPRITE_WIDTH, 0, SPRITE_WIDTH, SPRITE_HEIGHT });
	}
	else
		Immobile::destroy();
}

//----------------------------------------------------------
void Block::setActive(bool activeState)
{
	if (activeState)
		m_crumbling = false;
	Object::setActive(activeState);
}


