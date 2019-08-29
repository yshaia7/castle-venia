#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Item.h"


// - - - - - - - - - - - - - define section - - - - - -
#define SPRITE_WIDTH 15
#define SPRITE_HEIGHT 14

class AxeItem : public Item
{
public:
	AxeItem(sf::Vector2f location, ResourceManager& rManager);
	~AxeItem();


protected:
	void useItemEffect(std::weak_ptr<Player> player) { player.lock()->setWeapon(2); }
};

