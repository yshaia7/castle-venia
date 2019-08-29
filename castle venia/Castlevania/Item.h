#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Mobile.h"
#include "Player.h"

class Item : public Mobile, public std::enable_shared_from_this<Item>
{
public:
	Item() {}
	Item(sf::Vector2f location, ResourceManager& rManager);
	~Item();
	virtual void playerInteraction(std::weak_ptr<Player> player, std::vector<sf::RectangleShape>& rect); //Act based on player state
	virtual void useItemEffect(std::weak_ptr<Player> player) { playSound(); } 
	void draw(sf::RenderWindow& window);
protected:
	int m_itemType;
};

