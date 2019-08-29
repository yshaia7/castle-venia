#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "ResourceManager.h"

// - - - - - - - - - - - - - const section - - - - - -
const int stageInfoNum = 7;
const int SCREEN_WID = 768;
const int Epsilon = 30;
const int SIZE_OF_SCALA = 16;
const std::string stageInfoStr[stageInfoNum] = { "SCORE-", "TIME", "STAGE", "PLAYER","ENEMY","-","P-" };

// - - - - - - - - - - - - - enum section - - - - - -
enum information { SCORE = 0, TIME, STAGE, PLAYER, ENEMY, POWER, LIFE };

class StageDetails
{
public:
	StageDetails(ResourceManager &resource);
	~StageDetails();
	//translate the ditels from numbers to string and print them to the screen
	void updateStageDetails(int score, int time, int stage, int lives, int hearts, int enemyHealth, int playerHealth, std::tuple<sf::Texture&, int, int> weponTexture, ResourceManager& rManager);
	void draw(sf::RenderWindow& window);


private:
	sf::Text m_infoText[stageInfoNum]; //string save the SCORE TIME STAGE..
	void createStageInfo(ResourceManager &resource);
	std::string addZero(int leng, int val); //add zero before the score
	sf::RectangleShape m_photo[2]; //fram for weapen and heart texture
	sf::RectangleShape m_scalaLife[2][16]; //present the life remaind for player and boss
	sf::RectangleShape m_scalaInsideColor[2][16];

	int lifeLeft[2];
};
