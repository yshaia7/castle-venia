#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 

#include <vector>
#include <memory>
#include <fstream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "Object.h"
#include "Immobile.h"
#include "Character.h"
#include "Enemy.h"
#include "Item.h"
#include "Zombie.h"
#include "Bat.h"
#include "Wolf.h"
#include "Merman.h"
#include "GiantBat.h"
#include "Player.h"
#include "Stairs.h"
#include "Candlestick.h"
#include "Torch.h"
#include "Pit.h"
#include "Block.h"
#include "IntroScreen.h"
#include "IntroMovie.h"
#include "StageDetails.h"
// - - - - - - - - - - - - - const section - - - - - -
const int GAME_SPEED = 17; //Defines the run time of the game 
const double SCREEN_PORTION = 0.80; //Decides how much of the screen will be taken by game graphics
const int SCREEN_WIDTH = 768;
const int SCREEN_HEIGHT = 720;
const float CAMERA_HEIGHT = 90;
const float CAMERA_ZOOM = 0.3;

//- - - - - - - - - - - - struct sectoin - - - - - - 
struct levelTransitionTrigger {
	sf::RectangleShape trigger; //Where the stage transition trigger is located
	int type; //Type of stage transition
	int nextStage; //Which stage you'll transition to
	sf::Vector2f endPoint; //End location of transition
};

class Game
{
public:
	Game();
	~Game();
	void startGame();

private:
	std::vector<std::vector<std::shared_ptr<Enemy>>> m_enemies;
	std::vector<std::vector<std::shared_ptr<Immobile>>> m_immobObjects;
	std::vector<std::vector<std::shared_ptr<Stairs>>> m_stairs;
	std::vector<std::vector<sf::RectangleShape>> m_platforms;
	std::vector<sf::Vector2f> m_spawnPoint; //Decides where the character will appear in each stage after death
	sf::RectangleShape m_bossWall; //Appears when fighting the boss to block retreat
	sf::RenderWindow m_window;
	sf::Event m_events;
	sf::Clock m_clock;
	sf::View m_gameView; //Shows the gameplay (and not the status screen above)
	std::vector<sf::RectangleShape> m_backgrounds;
	std::vector<std::vector<int>> m_stageLimits; //The left and right corners of each stage
	std::shared_ptr<Player> m_hero;
	ResourceManager m_resources;
	IntroScreen m_introScreen{ m_resources }; //The start menu
	StageDetails m_status{ m_resources }; //The status screen above the gameplay
	std::vector<std::vector<levelTransitionTrigger>> m_transitions; //The transition animation between stages
	levelTransitionTrigger m_currentTransition; //The currently triggered screen transition
	sf::Music m_levelMusic; //The music that plays during regular gameplay
	sf::Music m_endGameMusic; //The music that plays after the boss has been defeated
	sf::Music m_bossFightMusic; //The music that plays during the boss fight
	std::vector<int> m_bossLocation; //The location of the boss in the enemy vector
	int m_currentStage; //The stage in which the player is currently in
	bool m_changingLevel; //Shows that there's currently a stage transition in progress
	bool m_bossActive;
	int m_changingCamera; //0 = normal camera, 1 = moving camera for screen transition, 2 = done moving camera for screen transition
	void createLevel(); //Create level details from a file
	void addStageLimits(std::fstream& levelFile);
	void addBackground(std::fstream& levelFile);
	void addSpawnPoint(std::fstream& levelFile);
	bool addPlatform(std::fstream& levelFile, std::vector<sf::RectangleShape>& newPlatformVector);
	bool addStairs(std::fstream& levelFile, std::vector<std::shared_ptr<Stairs>>& newStairVector);
	bool addEnemies(std::fstream& levelFile, std::vector<std::shared_ptr<Enemy>>& newEnemyVector);
	bool addObjects(std::fstream& levelFile, std::vector<std::shared_ptr<Immobile>>& newImmobileVector);
	bool addScreenTransition(std::fstream& levelFile, std::vector<levelTransitionTrigger>& newTransition);
	void run();
	bool restartStage(); //Restart stage after death
	void clearGame(); //Complete the game after the boss' defeat
	void resetLevelState(); //Reset stage parameters during death or stage completion
	void playLevelMusic();
	void playGameEndMusic();
	void userInput(); //Get input from the user
	void updateObjects(); //Update the game objects
	void draw();
	void levelTransition(); //Move between stages
	void moveCamera(); 
	void stopMusic();
};
