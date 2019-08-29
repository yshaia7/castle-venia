#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

// - - - - - - - - - - - - - const section - - - - - -
const int SCREEN_WIDT = 768;
const int SCREEN_HGT = 720;
const int OPEN_SPEED = 80;
const int EPSILON = 13;

class IntroScreen
{
public:
	IntroScreen(ResourceManager &resource);
	bool run(sf::RenderWindow &window, ResourceManager &resource);
	~IntroScreen();

private:
	void draw(sf::RenderWindow& window, int indexInmation);
	void reloadAndSet(ResourceManager &resource);
	void userKeyboardClick();

	sf::Texture * m_animation;
	sf::Sprite m_sprite[INTRO_ANIMATION_LENGTH];
	sf::RectangleShape m_buttonPress;
	sf::Clock m_clock;
	bool m_startGame = false;
	bool m_exit = false;
	sf::Text m_buttons[2];
	sf::Font m_font;
};

