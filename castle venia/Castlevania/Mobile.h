#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include "Object.h"

class Mobile : public Object
{
public:
	Mobile();
	~Mobile();
	virtual bool verticalCollision(sf::RectangleShape& rect); //Check collision from above or below
	virtual bool horizontalCollision(sf::RectangleShape& rect); //Check collision from the sides
	virtual void environmentCollisions(std::vector<sf::RectangleShape>& rect); //Use both of the collision functions above
	virtual bool collision(std::weak_ptr<Object> obj) { return m_hitbox.getGlobalBounds().intersects(obj.lock()->getHitbox().getGlobalBounds()); } //Check a simple intersection between objects
	void update() override;
	void setGravity(); //Use gravity on the object

protected:
	sf::Vector2f m_velocity;
	bool m_falling;
	bool getHorizontalCollision() { return m_horizontalCollision; }

private:
	bool m_horizontalCollision; //Save the result of the horizontal collision check for later use
};