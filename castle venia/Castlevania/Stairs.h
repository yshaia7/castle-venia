#pragma once
//- - - - - - - - - - - include sectoin - - - - - - 
#include "Object.h"
#include "Player.h"

// - - - - - - - - - - - - - define section - - - - - -
#define STAIRS_LENGTH 8 //The length of the stairs hitbox
#define STAIRS_HEIGHT 2 //The height of the stairs hitbox

class Stairs : public Object
{
public:
	Stairs(sf::Vector2f startPoint, int numOfStairs, int direction, int elevation);
	~Stairs();
	void playerInteraction(std::weak_ptr<Player> player);
private:
	sf::Vector2f m_location;
	int m_numOfStairs;
	int m_elevation; //0 = Bottom of stairs, 1 = Top of stairs
	DIRECTION m_direction; //Decides whether you climb to the left or right
};

