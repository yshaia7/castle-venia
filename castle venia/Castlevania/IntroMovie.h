#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include <vector>

// - - - - - - - - - - - - - define section - - - - - -
#define ANIMATION_DELAY 2
#define SPRITE_WIDTH 60
#define SPRITE_HEIGHT 32

// - - - - - - - - - - - - - const section - - - - - -
const float ANIMA_SPEED = 50;
const int BUT_NUM = 2;
const int NUM_OF_SPRITE_INTRO_MOVIE = 3;

class IntroMovie
{
public:
	IntroMovie(ResourceManager &resource);
	void run(sf::RenderWindow& window);
	~IntroMovie();

private:
	void moveAnimation();
	//get spritesheet and change animation for make it look like a real movment
	void loopingAnimation(sf::Sprite& m_sprite, int numOfFrames, int spriteWidth, int spriteHeight, int spriteY, int &animation_stage, int &m_animationDelay);
	void reloadAndSet(ResourceManager &resource);
	void Draw(sf::RenderWindow & window);
	sf::Sprite m_bats[2];
	sf::Sprite m_background;
	sf::Sprite m_player;
	sf::Sprite m_cloud;
	sf::Clock m_clock;
	sf::Sound m_sound;
	std::vector<int> m_animationStage;//save last pos for change the animation
	std::vector<int> m_animationDelay;//help to make animaion mov with some delay

};

