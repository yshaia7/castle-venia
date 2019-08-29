#include "IntroMovie.h"

//- - - - - - - - - - - - - - - - - - - - - - - - - - - -
IntroMovie::IntroMovie(ResourceManager &resource)
{
	reloadAndSet(resource);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - -
void IntroMovie::run(sf::RenderWindow & window )
{
	sf::Event event;
	m_clock.restart();
	m_sound.play();

	while (window.isOpen())
	{
		if (m_clock.getElapsedTime().asMilliseconds() >= 50)
		{
			moveAnimation();
			loopingAnimation(m_bats[0], 2, 10, 8, 0, m_animationStage[0], m_animationDelay[0]);
			loopingAnimation(m_bats[1], 2, 10, 8, 0, m_animationStage[1], m_animationDelay[1]);
			if (m_player.getPosition().x > 410)
				loopingAnimation(m_player, 3, SPRITE_WIDTH, SPRITE_HEIGHT, 0, m_animationStage[2], m_animationDelay[2]);
			else
				m_player.setTextureRect({ SPRITE_WIDTH * 3, SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT });

			m_clock.restart();
		}

		Draw(window);
	
	if (window.pollEvent(event))
		if (event.type == sf::Event::Closed)
		{
			window.close();
			exit(0);
		}
	if (m_sound.getStatus() == sf::SoundSource::Stopped)
	{
		sf::Clock timer;
		timer.restart();//when music stop go to the next screen(start the game)
		while (timer.getElapsedTime() < sf::seconds(1))
			continue;
		return;
	}
	}
	
}

//- - - - - - - - - - - - - - - - -
//change place of animation
void IntroMovie::moveAnimation()
{
	m_bats[0].move(1,-1);
	m_bats[1].move(-1, 0);
	m_cloud.move(-1.5, 0);
	if (m_player.getPosition().x > 410)
		m_player.move(-2.5, 0);

}

//- - - - - - - - - - - - - - - - - - -
//change animation and make it look real by movment happand
void IntroMovie::loopingAnimation(sf::Sprite& m_sprite,  int numOfFrames, int spriteWidth, int spriteHeight, int spriteY, int &animation_stage, int &m_animationDelay)
{
	if (m_animationDelay != ANIMATION_DELAY)
	{
		m_animationDelay++;
		return;
	}
	if (m_animationDelay == ANIMATION_DELAY && animation_stage == numOfFrames)
		animation_stage = 0;
	m_animationDelay = 0;
	m_sprite.setTextureRect({ spriteWidth * animation_stage, spriteY, spriteWidth, spriteHeight });
	animation_stage++;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - -
void IntroMovie::reloadAndSet(ResourceManager &resource)
{
	for (int i = 0; i < BUT_NUM; ++i)
	{
		m_bats[i].setTexture(resource.getBatIntroductionTexture());
		m_bats[i].setScale({ 3.2,  3.2});
		m_bats[i].setTextureRect(sf::IntRect(0,0,10,8));
	}
	m_sound.setBuffer(resource.getIntroductionSound());

	m_bats[0].setPosition({ 140 , 360 });
	m_bats[1].setPosition(440, 183);

	m_cloud.setTexture(resource.getCloudTexture());
	m_cloud.setPosition(768, 200);
	m_cloud.setScale(3, 3);

	m_background.setTexture(resource.getTransitionWindowTexture());
	m_background.setPosition({ 0,0 });
	m_background.scale(3, 3.4);

	for (int i = 0; i < NUM_OF_SPRITE_INTRO_MOVIE; ++i)
	{
		m_animationStage.push_back(0);
		m_animationDelay.push_back(0);
	}

	m_animationStage[0] = 1;
	m_player.setTexture(resource.getPlayerTexture());

	m_player.setTextureRect(sf::IntRect(0,0, SPRITE_WIDTH, SPRITE_HEIGHT));
	m_player.setPosition(620, 587);
	m_player.setScale(-3,3);
	
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - -
void IntroMovie::Draw(sf::RenderWindow & window)
{
	window.clear();
	window.draw(m_background);
	for (int i = 0; i < BUT_NUM; ++i)
		window.draw(m_bats[i]);
	window.draw(m_cloud);
	window.draw(m_player);
	window.display();
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - -
IntroMovie::~IntroMovie()
{
}
