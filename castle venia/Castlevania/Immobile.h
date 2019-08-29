#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Object.h"
#include "Player.h"
#include "Item.h"
#include "SmallHeart.h"
#include "LargeHeart.h"
#include "Food.h"
#include "WhipUpgrade.h"
#include "DaggerItem.h"
#include "AxeItem.h"
#include "BoomerangItem.h"



class Immobile : public Object, public std::enable_shared_from_this<Immobile>
{
public:
	Immobile() {}
	Immobile(sf::Vector2f location, int type, ResourceManager& rManager);
	~Immobile();
	virtual void playerInteraction(std::weak_ptr<Player> player, std::vector<sf::RectangleShape>& rect); //Act based on player state
	void destroy();
	void draw(sf::RenderWindow& window);
	void setType(int newType) { m_type = newType; } //Set the type of item that drops from the object
	int getType() { return m_type; }

private:
	std::vector<std::shared_ptr<Item>> m_item; //The item that's dropped from the object upon destruction
	ResourceManager m_resources;
	int m_type; //Type of item within the objecet
	void randomizeItem(); //Set a random item to emerge from the object
};