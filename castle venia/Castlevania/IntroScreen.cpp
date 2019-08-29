#include "IntroScreen.h"
#include <iostream>

//----------------------------------------------------------
IntroScreen::IntroScreen(ResourceManager &resource)
{
	reloadAndSet(resource);
}

//----------------------------------------------------------
bool IntroScreen::run(sf::RenderWindow &window, ResourceManager &resource)
{

	int indexAnimation = 1, animationIndexPlace = 0, timePassLoop = 0;
	sf::Event event;

	while (window.isOpen() && !m_startGame)
	{
		userKeyboardClick();

		for (; animationIndexPlace < indexAnimation; animationIndexPlace++)
			draw(window, indexAnimation);

		while (m_clock.getElapsedTime() >= sf::milliseconds(OPEN_SPEED) && !m_exit)
		{
			window.clear();
			draw(window, indexAnimation);
			++indexAnimation;
			if (indexAnimation == 16)
				indexAnimation = 14;
			m_clock.restart();
		}
		if (m_exit)
			return false;

		if (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(0);
			}
		}
	}
	while (m_startGame)
		if (m_clock.getElapsedTime().asSeconds() > 0.1) {
			draw(window, animationIndexPlace);
			m_buttonPress.setFillColor(sf::Color::Transparent);
			m_clock.restart();
			timePassLoop++;
			if (timePassLoop == EPSILON)
			{
				m_startGame = false;
				return true;
			}
		}

	return false;
}

//----------------------------------------------------------
IntroScreen::~IntroScreen()
{
}

//----------------------------------------------------------
void IntroScreen::draw(sf::RenderWindow & window, int indexAnimation)
{
	if (!m_startGame)
	{
		window.draw(m_sprite[0]);
		window.draw(m_buttons[0]);
		window.draw(m_buttons[1]);
	}
	else
		window.draw(m_buttonPress);

	window.draw(m_sprite[indexAnimation]);
	window.display();
}

//----------------------------------------------------------
void IntroScreen::reloadAndSet(ResourceManager &resource)
{
	m_animation = resource.getBackgroundSpritSheetTexture();

	for (int i = 0; i < INTRO_ANIMATION_LENGTH; i++)
	{
		m_sprite[i].setTexture(m_animation[i]);
		m_sprite[i].setScale(3, 3);
		m_sprite[i].setPosition(552, 318);

	}
	m_sprite[0].setPosition(0, 30);

	for (int i = 0; i < 2; i++)
	{
		m_buttons[i].setFont(resource.getFont());
		m_buttons[i].setFillColor(sf::Color::White);
		m_buttons[i].setOutlineColor(sf::Color::White);
		m_buttons[i].setCharacterSize(70);
		m_buttons[i].setPosition(225 + i * 105, 350 + i * 60);
	}
	m_buttons[0].setString("Start Game");
	m_buttons[1].setString("Exit");
	m_buttons[0].setOutlineThickness(1);

	m_buttonPress.setSize({ 340,60 });
	m_buttonPress.setFillColor(sf::Color::Black);
	m_buttonPress.setPosition(225, 378);
}

//----------------------------------------------------------
void IntroScreen::userKeyboardClick()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_buttons[0].setOutlineThickness(1);
		m_buttons[1].setOutlineThickness(0);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_buttons[0].setOutlineThickness(0);
		m_buttons[1].setOutlineThickness(1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		if (m_buttons[0].getOutlineThickness() > 0)
			m_startGame = true;
		else
			m_exit = true;


}