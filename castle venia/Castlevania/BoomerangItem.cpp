#include "BoomerangItem.h"

//----------------------------------------------------------
BoomerangItem::BoomerangItem(sf::Vector2f location, ResourceManager& rManager) : Item(location, rManager)
{
	setSoundBuffer(rManager.getCollectWeaponSound());
	setTexture(rManager.getBoomerandTexture());
	m_sprite.setTextureRect({ 0,0,SPRITE_WIDTH,SPRITE_HEIGHT });
	m_hitbox.setSize({ SPRITE_WIDTH, SPRITE_HEIGHT });
}

//----------------------------------------------------------
BoomerangItem::~BoomerangItem()
{
}
