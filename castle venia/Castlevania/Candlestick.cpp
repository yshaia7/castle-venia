#include "Candlestick.h"

//----------------------------------------------------------
Candlestick::Candlestick(sf::Vector2f location, int type, ResourceManager& rManager) : Immobile(location, type, rManager)
{
	setTexture(rManager.getCandleTexture());
	m_sprite.setTextureRect({ 0, 0, SPRITE_WIDTH, SPRITE_HEIGHT });
}

//----------------------------------------------------------
Candlestick::~Candlestick()
{
}

//----------------------------------------------------------
void Candlestick::playerInteraction(std::weak_ptr<Player> player, std::vector<sf::RectangleShape>& rect)
{
	Immobile::playerInteraction(player, rect);
	if (getActive())
		loopingAnimation(NUM_OF_FRAMES, SPRITE_WIDTH, SPRITE_HEIGHT, 0);
}
