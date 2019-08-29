#include "StageDetails.h"
#include <iostream>

//-----------------------------------------------------
StageDetails::StageDetails(ResourceManager &resource)
{
	createStageInfo(resource);
}

//-----------------------------------------------------
StageDetails::~StageDetails()
{
}

//-----------------------------------------------------
void StageDetails::updateStageDetails(int score, int time, int stage, int lives, int hearts, int enemyHealth, int playerHealth, std::tuple<sf::Texture&, int, int> weponTexture, ResourceManager& rManager)
{	//update values of current Details of player
	m_infoText[SCORE].setString(m_infoText[SCORE].getString().substring(0, 6) + addZero(6, score));
	m_infoText[TIME].setString(m_infoText[TIME].getString().substring(0, 4) + " " + addZero(4, time));
	m_infoText[STAGE].setString(m_infoText[STAGE].getString().substring(0, 5) + " " + addZero(2, stage));
	m_infoText[POWER].setString(m_infoText[POWER].getString().substring(0, 1) + " " + addZero(2, hearts));
	m_infoText[LIFE].setString(m_infoText[LIFE].getString().substring(0, 2) + " " + addZero(2, lives));

	//fill scala life of player with current life
	for (int place = 0; place < SIZE_OF_SCALA; place++)
	{
		if (place < playerHealth)
			m_scalaLife[0][place].setFillColor(sf::Color(128, 32, 0));
		else
			m_scalaLife[0][place].setFillColor(sf::Color(255, 255, 255));
	}

	//fill scala life of boss with current life
	for (int place = 0; place < SIZE_OF_SCALA; place++)
		if (place < enemyHealth)
			m_scalaLife[1][place].setFillColor(sf::Color(255, 125, 125));
		else
			m_scalaLife[1][place].setFillColor(sf::Color(255, 255, 255));

	lifeLeft[0] = playerHealth;
	lifeLeft[1] = enemyHealth;

	std::get<0>(weponTexture);

	m_photo[0].setTexture(&std::get<0>(weponTexture));
	m_photo[0].setTextureRect(sf::IntRect(0, 0, std::get<1>(weponTexture), std::get<2>(weponTexture)));
}

//-----------------------------------------------------		
void StageDetails::draw(sf::RenderWindow & window)
{
	for (int i = 0; i < stageInfoNum; ++i)
		window.draw(m_infoText[i]);

	for (int i = 0; i < 2; ++i)
		window.draw(m_photo[i]);

	for (int row = 0; row < 2; row++)
		for (int col = 0; col < SIZE_OF_SCALA; col++)
			window.draw(m_scalaLife[row][col]);

	for (int col = SIZE_OF_SCALA - 1; col >= lifeLeft[0]; col--)
		window.draw(m_scalaInsideColor[0][col]);

	for (int col = SIZE_OF_SCALA - 1; col >= lifeLeft[1]; col--)
		window.draw(m_scalaInsideColor[1][col]);

}

//-----------------------------------------------------
//create size and texture of Details of current Situation each moment in the game
void StageDetails::createStageInfo(ResourceManager &resource)
{
	m_photo[0].setSize({ 100, 50 });

	m_photo[0].setOutlineColor(sf::Color(255, 0, 0));
	m_photo[0].setOutlineThickness(2);
	m_photo[0].setPosition(Epsilon * 14, Epsilon * 2 - 5);

	m_photo[1].setSize({ 25, 25 });
	m_photo[1].setTexture(&resource.getSHeartTexture());
	m_photo[1].setPosition(Epsilon * 18 - 2, Epsilon + Epsilon - 10);

	for (int row = 0; row < 2; row++)
		for (int col = 0; col < SIZE_OF_SCALA; col++)
		{
			if (row == 0)
			{
				m_scalaLife[row][col].setSize({ 10, 20 });
				m_scalaLife[row][col].setFillColor(sf::Color(255, 255, 255));
				m_scalaLife[row][col].setOutlineColor(sf::Color(0, 0, 0));
				m_scalaLife[row][col].setPosition(150 + col * 15, Epsilon * 2 - 8);
				m_scalaLife[row][col].setOutlineThickness(2);

				m_scalaInsideColor[row][col].setSize({ 5, 10 });
				m_scalaInsideColor[row][col].setFillColor(sf::Color(0, 0, 0));
				m_scalaInsideColor[row][col].setPosition(150 + col * 15 + 3, Epsilon * 2 - 3);
			}
			else
			{
				m_scalaLife[row][col].setSize({ 10, 20 });
				m_scalaLife[row][col].setFillColor(sf::Color(255, 255, 255));
				m_scalaLife[row][col].setOutlineColor(sf::Color(0, 0, 0));
				m_scalaLife[row][col].setPosition(150 + col * 15, Epsilon * 2 + 20);
				m_scalaLife[row][col].setOutlineThickness(2);

				m_scalaInsideColor[row][col].setSize({ 5, 10 });
				m_scalaInsideColor[row][col].setFillColor(sf::Color(0, 0, 0));
				m_scalaInsideColor[row][col].setPosition(150 + col * 15 + 3, Epsilon * 2 + 25);
			}
		}

	for (int i = 0; i < stageInfoNum; ++i)
	{
		m_infoText[i].setFont(resource.getFont());
		m_infoText[i].setString(stageInfoStr[i]);
		m_infoText[i].setCharacterSize(40);

		if (i < 3)
			m_infoText[i].setPosition((SCREEN_WID / 3 + Epsilon * 2 - Epsilon / 2) * i, 0);
		else if (i == 3)
			m_infoText[i].setPosition(0, Epsilon);
		else if (i == 4)
			m_infoText[i].setPosition(0, Epsilon * 2);

		else if (i == 5)
			m_infoText[i].setPosition(Epsilon * 18 + 20, Epsilon);
		else if (i == 6)
			m_infoText[i].setPosition(Epsilon * 18, Epsilon + Epsilon);
	}
}

//-------------------------------------------------
std::string StageDetails::addZero(int leng, int val)
{
	std::string temp = std::to_string(val);
	int size = temp.size();
	std::string zeros(leng - size, '0');
	return zeros + temp;
}
