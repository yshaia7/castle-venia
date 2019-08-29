#include "WhipUpgrade.h"

//----------------------------------------------------------
WhipUpgrade::WhipUpgrade(sf::Vector2f location, ResourceManager& rManager) : Item(location, rManager)
{
	setSoundBuffer(rManager.getCollectWhipUpgradeSound());
	setTexture(rManager.getWhipUpgradeTexture());
}

//----------------------------------------------------------
WhipUpgrade::~WhipUpgrade()
{
}
