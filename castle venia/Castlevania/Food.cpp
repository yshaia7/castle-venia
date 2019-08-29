#include "Food.h"


//----------------------------------------------------------
Food::Food(sf::Vector2f location, ResourceManager& rManager) : Item(location, rManager)
{
	setSoundBuffer(rManager.getCollectWhipUpgradeSound());
	setTexture(rManager.getFoodTexture());
}

//----------------------------------------------------------
Food::~Food()
{
}
