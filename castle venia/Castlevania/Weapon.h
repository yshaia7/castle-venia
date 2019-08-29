#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Mobile.h"
#include <vector>

// - - - - - - - - - - - - - define section - - - - - -
#define SPRITE_WIDTH 0
#define SPRITE_HEIGHT 0

class Weapon : public Mobile
{
public:
	Weapon() {}
	Weapon(sf::Vector2f origin);
	~Weapon();
	const std::vector<std::shared_ptr<Object>> getAffectedCharacters() { return m_characters; } //Return characters hit by a weapon
	virtual void addCharacterHit(std::weak_ptr<Object> obj) { m_characters.push_back(obj.lock()); } //Add another character to the list
	bool collision(std::weak_ptr<Object> obj) { return m_hitbox.getGlobalBounds().intersects(obj.lock()->getHitbox().getGlobalBounds()); }
	virtual sf::Vector2f getWeaponSize() { return sf::Vector2f(SPRITE_WIDTH, SPRITE_HEIGHT); }

protected:
	std::vector<std::shared_ptr<Object>> m_characters; //Keep a list of which enemies were hit by a particular weapon, to ensure each one can only be hit once per weapon
};

