#include "AxeItem.h"

//----------------------------------------------------------
AxeItem::AxeItem(sf::Vector2f location, ResourceManager& rManager) : Item(location, rManager)
{
	setTexture(rManager.getAxeTexture());
	m_sprite.setTextureRect({ 0,0,SPRITE_WIDTH,SPRITE_HEIGHT });
	m_hitbox.setSize({SPRITE_WIDTH, SPRITE_HEIGHT});
	setSoundBuffer(rManager.getCollectWeaponSound());
}

//----------------------------------------------------------
AxeItem::~AxeItem()
{
}
