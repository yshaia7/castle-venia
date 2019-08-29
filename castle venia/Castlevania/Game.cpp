#include "Game.h"
#include <cstdlib>

//----------------------------------------------------------
using std::make_shared;

//----------------------------------------------------------
Game::Game()
{
	m_hero = make_shared<Player>(m_resources);
	m_gameView.setSize(SCREEN_WIDTH, SCREEN_HEIGHT * SCREEN_PORTION);
	m_gameView.zoom(CAMERA_ZOOM);
	m_gameView.setViewport(sf::FloatRect(0, (1 - SCREEN_PORTION), 1, SCREEN_PORTION));
	m_gameView.setCenter(SCREEN_WIDTH * CAMERA_ZOOM / 2, CAMERA_HEIGHT);
	m_levelMusic.openFromFile(m_resources.getLevelMusicFile());
	m_levelMusic.setLoop(true);
	m_endGameMusic.openFromFile(m_resources.getEndGameMusicFile());
	m_endGameMusic.setLoop(false);
	m_bossFightMusic.openFromFile(m_resources.getBossFightMusicFile());
	m_bossFightMusic.setLoop(true);
	m_clock.restart();
	m_changingLevel = false;
	m_changingCamera = 0;
	m_bossWall.setSize({ 3, 184 });
	m_bossActive = false;
	m_window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Castlevania");
	srand(time(NULL));
}

//----------------------------------------------------------
Game::~Game()
{
}

//----------------------------------------------------------
void Game::startGame()
{
	IntroMovie movie{ m_resources };
	createLevel();
	while (true)
	{
		m_window.clear();
		if (!m_introScreen.run(m_window, m_resources))
			return;
		movie.run(m_window);
		m_currentStage = 0;
		m_hero->resetLives();
		m_hero->setPosition(m_spawnPoint[0]);
		resetLevelState();
		run();
	}

}

//----------------------------------------------------------
void Game::createLevel()
{
	int numOfStages;
	std::fstream levelFile;
	levelFile.open("Level.txt");
	if (!levelFile) //File not found
		exit(EXIT_FAILURE);
		levelFile >> numOfStages;
		m_resources.setNumOfBackgrounds(numOfStages);
		for (int i = 0; i < numOfStages; i++)
		{
			
			//Create backgroung and stage limits for current stage
			addBackground(levelFile);
			addStageLimits(levelFile);
			addSpawnPoint(levelFile);
			//Add platforms to current stage
			std::vector<sf::RectangleShape> newPlatformVector;
			while (addPlatform(levelFile, newPlatformVector))
				continue;
			m_platforms.push_back(newPlatformVector);

			//Add stairs to current stage
			std::vector<std::shared_ptr<Stairs>> newStairVector;
			while (addStairs(levelFile, newStairVector))
				continue;
			m_stairs.push_back(newStairVector);

			//Add enemies to the current stage
			std::vector<std::shared_ptr<Enemy>> newEnemyVector;
			while (addEnemies(levelFile, newEnemyVector))
				continue;
			m_enemies.push_back(newEnemyVector);

			//Add objects to current stage
			std::vector<std::shared_ptr<Immobile>> newImmobileVector;
			while (addObjects(levelFile, newImmobileVector))
				continue;
			m_immobObjects.push_back(newImmobileVector);

			//Add level transition triggers to current stage
			std::vector<levelTransitionTrigger> newTransition;
			while (addScreenTransition(levelFile, newTransition))
				continue;
			m_transitions.push_back(newTransition);
		}
	levelFile.close();
}

//----------------------------------------------------------
void Game::addStageLimits(std::fstream & levelFile)
{
	int tempInt;
	std::vector<int> tempVector;
	levelFile >> tempInt;
	tempVector.push_back(tempInt);
	levelFile >> tempInt;
	tempVector.push_back(tempInt);
	m_stageLimits.push_back(tempVector);
}

//----------------------------------------------------------
void Game::addBackground(std::fstream & levelFile)
{
	std::string tempString;
	sf::Vector2f tempVector;
	levelFile >> tempString;
	m_backgrounds.push_back(sf::RectangleShape());
	m_backgrounds[m_backgrounds.size()-1].setTexture(&m_resources.getStageTexture(tempString));
	m_backgrounds.back().setSize(sf::Vector2f(m_backgrounds.back().getTexture()->getSize().x, m_backgrounds.back().getTexture()->getSize().y));
	levelFile >> tempVector.x;
	levelFile >> tempVector.y;
	m_backgrounds.back().setPosition(tempVector);
}

//----------------------------------------------------------
void Game::addSpawnPoint(std::fstream & levelFile)
{
	sf::Vector2f newPoint;
	levelFile >> newPoint.x;
	levelFile >> newPoint.y;
	m_spawnPoint.push_back(newPoint);
}

//----------------------------------------------------------
bool Game::addPlatform(std::fstream& levelFile, std::vector<sf::RectangleShape>& newPlatformVector)
{
	int input;
	sf::Vector2f tempVector;
	sf::RectangleShape newPlatform;
	levelFile >> input;
	if (input == -1)
		return false;
	tempVector.x = input;
	levelFile >> tempVector.y;
	newPlatform.setSize(tempVector);
	levelFile >> tempVector.x;
	levelFile >> tempVector.y;
	newPlatform.setPosition(tempVector);
	newPlatformVector.push_back(newPlatform);
	return true;
}

//----------------------------------------------------------
bool Game::addStairs(std::fstream& levelFile, std::vector<std::shared_ptr<Stairs>>& newStairVector)
{
	int input, numOfStairs, newDirection;
	sf::Vector2f tempVector;
	std::shared_ptr<Stairs> newStairs;
	levelFile >> input;
	if (input == -1)
		return false;
	tempVector.x = input;
	levelFile >> tempVector.y;
	levelFile >> numOfStairs;
	levelFile >> newDirection;
	levelFile >> input;
	newStairVector.push_back(make_shared<Stairs>(tempVector, numOfStairs, newDirection, input));
	return true;
}

//----------------------------------------------------------
bool Game::addEnemies(std::fstream & levelFile, std::vector<std::shared_ptr<Enemy>>& newEnemyVector)
{
	int input;
	sf::Vector2f tempVector;
	std::shared_ptr<Enemy> newEnemy;
	levelFile >> input;
	if (input == -1)
		return false;
	tempVector.x = input;
	levelFile >> tempVector.y;
	levelFile >> input;
	switch (input)
	{
		case 0:
			newEnemy = make_shared<Zombie>(tempVector, m_resources);
			newEnemyVector.push_back(newEnemy);
			break;
		case 1:
			newEnemy = make_shared<Bat>(tempVector, m_resources);
			newEnemyVector.push_back(newEnemy);
			break;
		case 2:
			newEnemy = make_shared<Wolf>(tempVector, m_resources);
			newEnemyVector.push_back(newEnemy);
			break;
		case 3:
			newEnemy = make_shared<Merman>(tempVector, m_resources);
			newEnemyVector.push_back(newEnemy);
			break;
		case 4:
			//Add boss
			std::vector<int> enemyBounds;
			levelFile >> input;
			enemyBounds.push_back(input);
			levelFile >> input;
			enemyBounds.push_back(input);
			newEnemy = make_shared<GiantBat>(tempVector, m_resources, enemyBounds);
			newEnemyVector.push_back(newEnemy);
			m_bossLocation.push_back(m_backgrounds.size() - 1);
			m_bossLocation.push_back(newEnemyVector.size() - 1);
			m_bossWall.setPosition(sf::Vector2f(enemyBounds[0], 0));
			break;
	}
	return true;
}

//----------------------------------------------------------
bool Game::addObjects(std::fstream& levelFile, std::vector<std::shared_ptr<Immobile>>& newImmobileVector)
{
	int input;
	sf::Vector2f tempVector;
	std::shared_ptr<Immobile> newImmobile;
	levelFile >> input;
	if (input == -1)
		return false;
	tempVector.x = input;
	levelFile >> tempVector.y;
	levelFile >> input;
	switch (input)
	{
		case 0:
			levelFile >> input;
			newImmobile = make_shared<Candlestick>(tempVector, input, m_resources);
			newImmobileVector.push_back(newImmobile);
			break;
		case 1:
			levelFile >> input;
			newImmobile = make_shared<Torch>(tempVector, input,  m_resources);
			newImmobileVector.push_back(newImmobile);
			break;
		case 2:
			newImmobile = make_shared<Pit>(sf::Vector2f(m_stageLimits.back()[1] - m_stageLimits.back()[0], 20), tempVector);
			newImmobileVector.push_back(newImmobile);
			break;
		case 3:
			newImmobile = make_shared<Block>(tempVector, m_resources);
			newImmobileVector.push_back(newImmobile);
			break;
	}
	return true;
}

//----------------------------------------------------------
bool Game::addScreenTransition(std::fstream & levelFile, std::vector<levelTransitionTrigger>& newTransition)
{
	levelTransitionTrigger tempTrigger;
	sf::Vector2f tempVector;
	int tempInt;
	levelFile >> tempInt;
	if (tempInt == -1)
		return false;
	tempTrigger.type = tempInt;
	levelFile >> tempVector.x;
	levelFile >> tempVector.y;
	tempTrigger.trigger.setSize({ 32,2 });
	tempTrigger.trigger.setPosition(tempVector);
	levelFile >> tempInt;
	tempTrigger.nextStage = tempInt;
	levelFile >> tempVector.x;
	levelFile >> tempVector.y;
	tempTrigger.endPoint = tempVector;
	newTransition.push_back(tempTrigger);
	return true;
}

//----------------------------------------------------------
void Game::run()
{
	playLevelMusic();
	while (m_window.isOpen())
	{
		if (m_clock.getElapsedTime() >= sf::milliseconds(GAME_SPEED))
		{
		if (!m_changingLevel)
			userInput();
		updateObjects();
		//If finished the stage or died
		if (m_hero->getLevelClearState())
		{
			clearGame();
			return;
		}
		if (m_hero->getRemovalFlagState())
		{
			if (!restartStage())
				return;
		}

		moveCamera();
		draw();
		m_clock.restart();
		}
	}
}

//----------------------------------------------------------
bool Game::restartStage()
{
	stopMusic();
	m_resources.playLostLife();
	resetLevelState();
	if (m_hero->getLives() < 0)
		return false;
	playLevelMusic();
	return true;
}

//----------------------------------------------------------
void Game::clearGame()
{
	resetLevelState();
	playGameEndMusic();
	while (m_endGameMusic.getStatus() != sf::SoundSource::Stopped)
		continue;
}

//----------------------------------------------------------
void Game::resetLevelState()
{
	stopMusic();
	m_hero->resetScore();
	m_hero->defaultState();
	m_hero->resetTimer();
	m_hero->setRemoveFlag(false);
	m_hero->setMidRemovalFlag(false);
	m_hero->restoreHealth();
	m_hero->setPosition(m_spawnPoint[m_currentStage]);
	m_hero->setWeapon(0);
	//Release camera lock
	if (m_hero->getCameraLock())
	{
		m_hero->setCameraLock(false);
		m_platforms[m_bossLocation[0]].pop_back();
	}
	for (auto i : m_enemies[m_currentStage])
	{
		i->setActive(false);
		i->disableWeapons();
	}
	m_enemies[m_bossLocation[0]][m_bossLocation[1]]->restoreHealth(); //Restore boss' health
	//Reactivate objects
	for (auto i : m_immobObjects)
		for (auto k : i)
			k->setActive(true);
	m_hero->resetTimer();
	m_hero->setLevelClearState(false);
	m_hero->setCameraLock(false);
	m_hero->resetWhip();
	m_hero->resetHearts();
}

//----------------------------------------------------------
void Game::playLevelMusic()
{
	if (m_levelMusic.getStatus() == sf::SoundSource::Stopped)
		m_levelMusic.play();
	else
		m_levelMusic.stop();
}

//----------------------------------------------------------
void Game::playGameEndMusic()
{
	m_endGameMusic.play();
	while (m_endGameMusic.getStatus() != sf::SoundSource::Stopped)
		continue;
	m_endGameMusic.stop();
}

//----------------------------------------------------------
void Game::userInput()
{
	if (m_window.pollEvent(m_events))
	{
		if (m_events.type == sf::Event::Closed)
		{
			m_window.close();
			exit(0);
		}
		if (m_events.type == sf::Event::KeyPressed)
			m_hero->getButtonPress(m_events.key.code);
		else if (m_events.type == sf::Event::KeyReleased)
			m_hero->getButtonRelease(m_events.key.code);
	}
}

//----------------------------------------------------------
void Game::updateObjects()
{
	//Change stage
	if (m_changingLevel || m_changingCamera != 0)
	{
		levelTransition();
		return;
	}

	//Set stage to transitioning state
	for (auto i : m_transitions[m_currentStage])
	{
		if (m_hero->getHitbox().getGlobalBounds().intersects(i.trigger.getGlobalBounds()) && (!m_changingLevel && i.type == 0 || i.type == 1 && m_hero->getClimbingState()) && !m_hero->getFallingState())
		{
			m_currentTransition = i;
			if (i.type == 0)
				m_hero->defaultState();
			m_changingLevel = true;
			return;
		}
	}

	//Check enemy and player interactions
	for (int i = 0; i < m_enemies[m_currentStage].size(); i++)
	{
		m_enemies[m_currentStage][i]->playerInteraction(m_hero);
		m_enemies[m_currentStage][i]->environmentCollisions(m_platforms[m_currentStage]);
	}

	//Check player interaction with the stairs
	for (int i = 0; i < m_stairs[m_currentStage].size(); i++)
		m_stairs[m_currentStage][i]->playerInteraction(m_hero);

	//Check object interaction with the player
	for (int i = 0; i < m_immobObjects[m_currentStage].size(); i++)
		m_immobObjects[m_currentStage][i]->playerInteraction(m_hero, m_platforms[m_currentStage]);

	//Spawn wall to keep player in the boss arena and play music
	if (m_hero->getCameraLock() && m_platforms[m_bossLocation[0]].back().getSize() != m_bossWall.getSize() && m_platforms[m_bossLocation[0]].back().getPosition() != m_bossWall.getPosition())
	{
		m_bossActive = true;
		m_platforms[m_bossLocation[0]].push_back(m_bossWall);
		stopMusic();
		m_bossFightMusic.play();
	}

	m_hero->update(m_platforms[m_currentStage]);

	//Update status screen
	m_status.updateStageDetails(m_hero->getScore(), m_hero->getTime(), m_currentStage + 1, m_hero->getLives(), m_hero->getHearts(), m_enemies[m_bossLocation[0]][m_bossLocation[1]]->getHealth(), m_hero->getHealth(), m_hero->getWeapon(), m_resources);
}

//----------------------------------------------------------
void Game::draw()
{
	m_window.clear();
	m_window.setView(m_gameView);
	for (auto i : m_backgrounds)
		m_window.draw(i);

	for (auto i : m_enemies[m_currentStage])
		i->draw(m_window);
	for (auto i : m_immobObjects[m_currentStage])
		i->draw(m_window);
	m_hero->draw(m_window);
	m_window.setView(m_window.getDefaultView());
	m_status.draw(m_window);
	m_window.display();
}

//----------------------------------------------------------
void Game::levelTransition()
{
	//If finished switching stage
	if (m_changingCamera == 2 && !m_changingLevel)
	{
		m_currentStage = m_currentTransition.nextStage;
		m_changingCamera = 0;
		return;
	}
	//Moving stage from left to right
	if (m_currentTransition.type == 0)
	{
		if (m_changingCamera == 0)
		{
			m_changingCamera = 1;
			return;
		}
		//Moving player towards new stage
		else if (m_changingCamera == 2)
		{
			if (m_hero->getHitbox().getPosition().x < m_currentTransition.endPoint.x)
				m_hero->automatedMovement(RIGHT);
			else
			{
				m_changingCamera = 1;
				m_changingLevel = false;
			}
		}
	}
	//Instant stage switching (when moving by stairs)
	else if (m_currentTransition.type == 1)
	{
		if (m_changingCamera == 0)
		{
			m_hero->setPosition(m_currentTransition.endPoint);
			m_changingCamera = 1;
			m_currentStage = m_currentTransition.nextStage;
		}
		else
		{
			m_changingCamera = 0;
			m_changingLevel = false;
		}
	}
}

//----------------------------------------------------------
void Game::moveCamera()
{
	//Disable camera movement when fighting the boss;
	if (m_hero->getCameraLock())
		return;

	//Move camera according to stage trasition
	if (m_changingLevel && m_currentTransition.type == 0)
	{
		if (m_changingCamera == 1)
			if (m_gameView.getCenter().x < m_stageLimits[m_currentStage][1])
				m_gameView.move(1.5, 0);
			else
				m_changingCamera = 2;
		return;
	}
	else if (!m_changingLevel && m_changingCamera == 1 && m_currentTransition.type == 0)
	{
		if (m_gameView.getCenter().x < m_stageLimits[m_currentTransition.nextStage][0] + (SCREEN_WIDTH * CAMERA_ZOOM / 2))
			m_gameView.move(1.5, 0);
		else
			m_changingCamera = 2;
		return;
	}
	else if (m_currentTransition.type == 1 && m_changingCamera == 1)
	{
		m_gameView.setCenter({ m_stageLimits[m_currentStage][0] + (SCREEN_WIDTH * CAMERA_ZOOM / 2), CAMERA_HEIGHT  + m_backgrounds[m_currentStage].getGlobalBounds().top});
		m_changingCamera = 2;
		return;
	}

	//Move camera according to player movement
	if (m_hero->getLocation().x > m_stageLimits[m_currentStage][0] + (SCREEN_WIDTH * CAMERA_ZOOM / 2) && m_hero->getLocation().x < m_stageLimits[m_currentStage][1] - (SCREEN_WIDTH * CAMERA_ZOOM / 2))
		m_gameView.setCenter({ m_hero->getLocation().x, CAMERA_HEIGHT + m_backgrounds[m_currentStage].getGlobalBounds().top });
	else if (abs(m_stageLimits[m_currentStage][1] - m_hero->getLocation().x) < (SCREEN_WIDTH * CAMERA_ZOOM / 2))
		m_gameView.setCenter({ m_stageLimits[m_currentStage][1] - (SCREEN_WIDTH * CAMERA_ZOOM / 2), CAMERA_HEIGHT + m_backgrounds[m_currentStage].getGlobalBounds().top });
	else
		m_gameView.setCenter({ m_stageLimits[m_currentStage][0] + (SCREEN_WIDTH * CAMERA_ZOOM / 2), CAMERA_HEIGHT + m_backgrounds[m_currentStage].getGlobalBounds().top });
}

//----------------------------------------------------------
void Game::stopMusic()
{
	m_levelMusic.stop();
	m_bossFightMusic.stop();
	m_endGameMusic.stop();
}
