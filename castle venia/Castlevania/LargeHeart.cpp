#include "LargeHeart.h"


//----------------------------------------------------------
LargeHeart::LargeHeart(sf::Vector2f location, ResourceManager& rManager) : Item(location, rManager)
{
	setSoundBuffer(rManager.getCollectHeartSound());
	setTexture(rManager.getLHeartTexture());
}

//----------------------------------------------------------
LargeHeart::~LargeHeart()
{
}
