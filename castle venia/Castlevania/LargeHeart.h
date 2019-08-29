#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Item.h"

class LargeHeart : public Item
{
public:
	LargeHeart(sf::Vector2f location, ResourceManager& rManager);
	~LargeHeart();

protected:
	void useItemEffect(std::weak_ptr<Player> player) { player.lock()->addHearts(5); }
};

