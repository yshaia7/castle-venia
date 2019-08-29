#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ResourceManager.h"
#include <vector>

// - - - - - - - - - - - - - const section - - - - - -
const float GRAVITY = 0.26;

// - - - - - - - - - - - - - define section - - - - - -
#define ANIMATION_DELAY 4

class Object
{
public:
	Object();
	~Object();
	virtual void draw(sf::RenderWindow& window);
	virtual void setTexture(sf::Texture& texture);
	virtual void setTexture(ResourceManager& rManager) {}
	virtual bool collision(std::weak_ptr<Object> obj) { return m_hitbox.getGlobalBounds().intersects(obj.lock()->getHitbox().getGlobalBounds()); }
	virtual void update() {}
	virtual void setActive(bool activeState);
	bool getActive() { return m_isActive; }
	void setPosition(sf::Vector2f newPos);
	sf::Vector2f getPosition() { return m_hitbox.getPosition(); }
	const sf::RectangleShape& getHitbox() { return m_hitbox; } //Return the character's hitbox
	virtual bool getRemovalFlagState() { return m_removeFlag; } //Return whether the object should be removed (by being attacked, being too far etc)
	void setRemoveFlag(bool state) { m_removeFlag = state; }
	virtual bool getMidRemovalFlagState() { return m_midRemoval; } //Return whether a character is playing its death animation and will be removed soon
	void setMidRemovalFlag(bool state) { m_midRemoval = state; }
	virtual void getHit(std::weak_ptr<Object> hitObj) { destroy(); }
	virtual void destroy() { m_isActive = false; }
	void loopingAnimation(int numOfFrames, int spriteWidth, int spriteHeight, int spriteY); //Play an animation that will start again from the first frame after playing the last frame
	void setSoundBuffer(sf::SoundBuffer& buffer) { m_objectSound.setBuffer(buffer); }
	void playSound() { m_objectSound.play(); }
	bool isSoundStopped() { return (m_objectSound.getStatus() == sf::SoundSource::Stopped); }
	void setVolume(int volume) { m_objectSound.setVolume(volume); } //Set sound volume

protected:
	sf::Sprite m_sprite;
	sf::RectangleShape m_hitbox;
	bool m_removeFlag; //Marks that the object should be removed
	bool m_midRemoval; //An object that will soon be removed (displays an animation etc)
	int m_animationStage; //Which frame of animation the object is currently on
	int m_animationDelay; //The delay between each frame of animation
	

private:
	bool m_isActive; //Whether the object is currently activated
	sf::Sound m_objectSound; //The sound emitted by the object
};

