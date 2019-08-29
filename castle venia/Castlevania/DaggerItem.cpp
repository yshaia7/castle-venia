#include "DaggerItem.h"


//----------------------------------------------------------
DaggerItem::DaggerItem(sf::Vector2f location, ResourceManager& rManager) : Item(location, rManager)
{
	setSoundBuffer(rManager.getCollectWeaponSound());
	setTexture(rManager.getDaggerTexture());
}

//----------------------------------------------------------
DaggerItem::~DaggerItem()
{
}
