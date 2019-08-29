#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Item.h"

class Food : public Item
{
public:
	Food(sf::Vector2f location, ResourceManager& rManager);
	~Food();

protected:
	void useItemEffect(std::weak_ptr<Player> player) { player.lock()->restoreHealth(); }
};

