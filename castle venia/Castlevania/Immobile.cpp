#include "Immobile.h"


//----------------------------------------------------------
Immobile::Immobile(sf::Vector2f location, int type, ResourceManager& rManager)
{
	setSoundBuffer(rManager.getObjectHitSound());
	setPosition(location);
	m_resources = rManager;
	setType(type);
}

//----------------------------------------------------------
Immobile::~Immobile()
{
}

//----------------------------------------------------------
void Immobile::playerInteraction(std::weak_ptr<Player> player, std::vector<sf::RectangleShape>& rect)
{
	//Allows the player to interact with the dropped item
	if (m_item.size() > 0)
	{
		if (m_item[0]->getActive())
		{
			m_item[0]->playerInteraction(player, rect);
			return;
		}
		else if (m_item[0]->isSoundStopped())
			m_item.pop_back();
	}
	if (!getActive())
		return;
	player.lock()->checkAttackTarget(shared_from_this());
}

void Immobile::destroy()
{
	Object::destroy();
	switch (m_type)
	{
		case -1:
		{
			randomizeItem();
			break;
		}
		case 0:
		{
			m_item.push_back(std::make_shared<WhipUpgrade>(getPosition(), m_resources));
			break;
		}
		case 1:
		{
			m_item.push_back(std::make_shared<Food>(getPosition(), m_resources));
			break;
		}
		case 2:
		{
			m_item.push_back(std::make_shared<SmallHeart>(getPosition(), m_resources));
			break;
		}
		case 3:
		{
			m_item.push_back(std::make_shared<LargeHeart>(getPosition(), m_resources));
			break;
		}
		case 4:
		{
			m_item.push_back(std::make_shared<DaggerItem>(getPosition(), m_resources));
			break;
		}
		case 5:
		{
			m_item.push_back(std::make_shared<AxeItem>(getPosition(), m_resources));
			break;
		}
		case 6:
		{
			m_item.push_back(std::make_shared<BoomerangItem>(getPosition(), m_resources));
			break;
		}
	}
}

//----------------------------------------------------------
void Immobile::draw(sf::RenderWindow& window)
{
	if (getActive())
		Object::draw(window);
	if (m_item.size() > 0)
		m_item[0]->draw(window);
}

//----------------------------------------------------------
void Immobile::randomizeItem()
{
	//Randomize whether the next item will be a weapon or ammo
	int itemType = rand() % 10;

	//Get random weapon
	if (itemType >= 0 && itemType <= 2)
	{
		itemType = rand() % 3;
		switch (itemType)
		{
			case 0:
				m_item.push_back(std::make_shared<DaggerItem>(getPosition(), m_resources));
				break;
			case 1:
				m_item.push_back(std::make_shared<AxeItem>(getPosition(), m_resources));
				break;
			case 2:
				m_item.push_back(std::make_shared<BoomerangItem>(getPosition(), m_resources));
				break;
		}
	}
	//Get ammo
	else
	{
		itemType = rand() % 5;
		if (itemType == 0 || itemType == 1)
			m_item.push_back(std::make_shared<LargeHeart>(getPosition(), m_resources));
		else
			m_item.push_back(std::make_shared<SmallHeart>(getPosition(), m_resources));
	}
}
