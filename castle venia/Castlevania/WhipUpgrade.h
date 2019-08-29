#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Item.h"

class WhipUpgrade : public Item
{
public:
	WhipUpgrade(sf::Vector2f location, ResourceManager& rManager);
	~WhipUpgrade();
	
protected:
	void useItemEffect(std::weak_ptr<Player> player) { player.lock()->updgradeWhip(); }
};

