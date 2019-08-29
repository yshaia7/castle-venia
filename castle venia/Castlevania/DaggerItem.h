#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Item.h"

class DaggerItem : public Item
{
public:
	DaggerItem(sf::Vector2f location, ResourceManager& rManager);
	~DaggerItem();

protected:
	void useItemEffect(std::weak_ptr<Player> player) { player.lock()->setWeapon(1); }
};

