#include "Item.h"


//----------------------------------------------------------
Item::Item(sf::Vector2f location, ResourceManager& rManager)
{
	setPosition(location);
}

//----------------------------------------------------------
Item::~Item()
{
}

//----------------------------------------------------------
void Item::playerInteraction(std::weak_ptr<Player> player, std::vector<sf::RectangleShape>& rect)
{
	if (!getActive())
		return;

	if (player.lock()->collision(shared_from_this()))
	{
		useItemEffect(player);
		playSound();
		setActive(false);
	}
	environmentCollisions(rect);
	Mobile::update();
}

//----------------------------------------------------------
void Item::draw(sf::RenderWindow & window)
{
	if (!getActive())
		return;
	Object::draw(window);
}
