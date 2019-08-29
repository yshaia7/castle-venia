#include "ResourceManager.h"


//----------------------------------------------------------
ResourceManager::ResourceManager()
{
}

//----------------------------------------------------------
ResourceManager::~ResourceManager()
{
}

//----------------------------------------------------------
sf::Texture& ResourceManager::getPlayerTexture()
{
	if (m_playerTexture.getSize() == sf::Vector2u(0, 0))
		m_playerTexture.loadFromFile("Textures/Player.png");
	return m_playerTexture;
}

//----------------------------------------------------------
sf::Texture & ResourceManager::getEmptyTexture()
{
	if (m_emptyTexture.getSize() == sf::Vector2u(0, 0))
		m_emptyTexture.loadFromFile("Textures/EmptyTexture.png");
	return m_emptyTexture;
}

//----------------------------------------------------------
sf::Texture& ResourceManager::getDaggerTexture()
{
	if (m_daggerTexture.getSize() == sf::Vector2u(0, 0))
		m_daggerTexture.loadFromFile("Textures/Dagger.png");
	return m_daggerTexture;
}

//----------------------------------------------------------
sf::Texture& ResourceManager::getAxeTexture()
{
	if (m_axeTexture.getSize() == sf::Vector2u(0, 0))
		m_axeTexture.loadFromFile("Textures/Axe.png");
	return m_axeTexture;
}

//----------------------------------------------------------
sf::Texture & ResourceManager::getBoomerandTexture()
{
	if (m_boomerangTexture.getSize() == sf::Vector2u(0, 0))
		m_boomerangTexture.loadFromFile("Textures/Boomerang.png");
	return m_boomerangTexture;
}

//----------------------------------------------------------
sf::Texture & ResourceManager::getZombieTexture()
{
	if (m_zombieTexture.getSize() == sf::Vector2u(0, 0))
		m_zombieTexture.loadFromFile("Textures/Zombie.png");
	return m_zombieTexture;
}

//----------------------------------------------------------
sf::Texture & ResourceManager::getBatTexture()
{
	if (m_batTexture.getSize() == sf::Vector2u(0, 0))
		m_batTexture.loadFromFile("Textures/Bat.png");
	return m_batTexture;
}

//----------------------------------------------------------
sf::Texture & ResourceManager::getWolfTexture()
{
	if (m_wolfTexture.getSize() == sf::Vector2u(0, 0))
		m_wolfTexture.loadFromFile("Textures/Wolf.png");
	return m_wolfTexture;
}

//----------------------------------------------------------
sf::Texture & ResourceManager::getMermanTexture()
{
	if (m_mermanTexture.getSize() == sf::Vector2u(0, 0))
		m_mermanTexture.loadFromFile("Textures/Merman.png");
	return m_mermanTexture;
}

//----------------------------------------------------------
sf::Texture & ResourceManager::getGiantBatTexture()
{
	if (m_giantBatTexture.getSize() == sf::Vector2u(0, 0))
		m_giantBatTexture.loadFromFile("Textures/GiantBat.png");
	return m_giantBatTexture;
}

//----------------------------------------------------------
sf::Texture & ResourceManager::getCandleTexture()
{
	if (m_candleTexture.getSize() == sf::Vector2u(0, 0))
		m_candleTexture.loadFromFile("Textures/Candle.png");
	return m_candleTexture;
}

//----------------------------------------------------------
sf::Texture & ResourceManager::getTorchTexture()
{
	if (m_torchTexture.getSize() == sf::Vector2u(0, 0))
		m_torchTexture.loadFromFile("Textures/Torch.png");
	return m_torchTexture;
}

//----------------------------------------------------------
sf::Texture & ResourceManager::getBlockTexture()
{
	if (m_blockTexture.getSize() == sf::Vector2u(0, 0))
		m_blockTexture.loadFromFile("Textures/Block.png");
	return m_blockTexture;
}

//----------------------------------------------------------
sf::Texture & ResourceManager::getSHeartTexture()
{
	if (m_sHeartTexture.getSize() == sf::Vector2u(0, 0))
		m_sHeartTexture.loadFromFile("Textures/Heart.png");
	return m_sHeartTexture;
}

//----------------------------------------------------------
sf::Texture & ResourceManager::getLHeartTexture()
{
	if (m_lHeartTexture.getSize() == sf::Vector2u(0, 0))
		m_lHeartTexture.loadFromFile("Textures/LargeHeart.png");
	return m_lHeartTexture;
}

//----------------------------------------------------------
sf::Texture & ResourceManager::getFoodTexture()
{
	if (m_foodTexture.getSize() == sf::Vector2u(0,0))
		m_foodTexture.loadFromFile("Textures/Food.png");
	return m_foodTexture;
}

//----------------------------------------------------------
sf::Texture & ResourceManager::getWhipUpgradeTexture()
{
	if (m_whipUpgradeTexture.getSize() == sf::Vector2u(0, 0))
		m_whipUpgradeTexture.loadFromFile("Textures/Whip.png");
	return m_whipUpgradeTexture;
}

//----------------------------------------------------------
sf::Texture & ResourceManager::getFireballTexture()
{
	if (m_fireballTexture.getSize() == sf::Vector2u(0, 0))
		m_fireballTexture.loadFromFile("Textures/Fireball.png");
	return m_fireballTexture;
}

//----------------------------------------------------------
sf::Texture& ResourceManager::getStageTexture(std::string filename)
{
	static int numOfTextures = 0;
	sf::Texture tempTexture;
	tempTexture.loadFromFile(filename);
	m_stageTextures[numOfTextures] = tempTexture;
	numOfTextures++;
	return m_stageTextures[numOfTextures - 1];
}

//----------------------------------------------------------
sf::Texture * ResourceManager::getBackgroundSpritSheetTexture()
{
	static bool firstTimeLoad = false;
	if (!firstTimeLoad)
	{
		int i = 0;
		m_SpritSheetTexture[i].loadFromFile("Textures/OpenScreen/1.png");
		i++;
		m_SpritSheetTexture[i].loadFromFile("Textures/OpenScreen/2.png");
		i++;
		m_SpritSheetTexture[i].loadFromFile("Textures/OpenScreen/3.png");
		i++;
		m_SpritSheetTexture[i].loadFromFile("Textures/OpenScreen/4.png");
		i++;
		m_SpritSheetTexture[i].loadFromFile("Textures/OpenScreen/5.png");
		i++;
		m_SpritSheetTexture[i].loadFromFile("Textures/OpenScreen/6.png");
		i++;
		m_SpritSheetTexture[i].loadFromFile("Textures/OpenScreen/7.png");
		i++;
		m_SpritSheetTexture[i].loadFromFile("Textures/OpenScreen/8.png");
		i++;
		m_SpritSheetTexture[i].loadFromFile("Textures/OpenScreen/9.png");
		i++;
		m_SpritSheetTexture[i].loadFromFile("Textures/OpenScreen/10.png");
		i++;
		m_SpritSheetTexture[i].loadFromFile("Textures/OpenScreen/11.png");
		i++;
		m_SpritSheetTexture[i].loadFromFile("Textures/OpenScreen/12.png");
		i++;
		m_SpritSheetTexture[i].loadFromFile("Textures/OpenScreen/13.png");
		i++;
		m_SpritSheetTexture[i].loadFromFile("Textures/OpenScreen/14.png");
		i++;
		m_SpritSheetTexture[i].loadFromFile("Textures/OpenScreen/15.png");
		i++;
		m_SpritSheetTexture[i].loadFromFile("Textures/OpenScreen/16.png");
		i++;
		firstTimeLoad = true;
	}
	return m_SpritSheetTexture;

}

//----------------------------------------------------------
sf::Texture & ResourceManager::getBatIntroductionTexture()
{
	if (m_BatIntroduction.getSize() == sf::Vector2u(0, 0))
		m_BatIntroduction.loadFromFile("Textures/BatIntroduction.png");
	return m_BatIntroduction;
}

//----------------------------------------------------------
sf::Texture & ResourceManager::getCloudTexture()
{
	if (m_cloud.getSize() == sf::Vector2u(0, 0))
		m_cloud.loadFromFile("Textures/Cloud.png");
	return m_cloud;
}

//----------------------------------------------------------
sf::Texture & ResourceManager::getTransitionWindowTexture()
{
	if (m_transitionWindow.getSize() == sf::Vector2u(0, 0))
		m_transitionWindow.loadFromFile("Textures/TransitionWindow.png");
	return m_transitionWindow;
}

//----------------------------------------------------------
sf::SoundBuffer & ResourceManager::getObjectHitSound()
{
	if (m_objectHitSound.getSampleCount() == 0)
		m_objectHitSound.loadFromFile("Sounds/Destroyed.ogg");
	return m_objectHitSound;
}

//----------------------------------------------------------
sf::SoundBuffer & ResourceManager::getCollectHeartSound()
{
	if (m_collectHeartSound.getSampleCount() == 0)
		m_collectHeartSound.loadFromFile("Sounds/CollectHeart.ogg");
	return m_collectHeartSound;
}

//----------------------------------------------------------
sf::SoundBuffer & ResourceManager::getCollectWeaponSound()
{
	if (m_collectWeaponSound.getDuration() == sf::microseconds(0))
		m_collectWeaponSound.loadFromFile("Sounds/Collect Weapon.ogg");
	return m_collectWeaponSound;
}

//----------------------------------------------------------
sf::SoundBuffer & ResourceManager::getCollectWhipUpgradeSound()
{
	if (m_collectWhipUpgradeSound.getSampleCount() == 0)
		m_collectWhipUpgradeSound.loadFromFile("Sounds/UpgradeWhip.ogg");
	return m_collectWhipUpgradeSound;
}

//----------------------------------------------------------
sf::SoundBuffer & ResourceManager::getThrowWeaponSound()
{
	if (m_throwWeaponSound.getSampleCount() == 0)
		m_throwWeaponSound.loadFromFile("Sounds/Throw.ogg");
	return m_throwWeaponSound;
}

//----------------------------------------------------------
sf::SoundBuffer & ResourceManager::getWhipSound()
{
	if (m_whipSound.getSampleCount() == 0)
		m_whipSound.loadFromFile("Sounds/Hit.ogg");
	return m_whipSound;
}

//----------------------------------------------------------
sf::SoundBuffer & ResourceManager::getDamageSound()
{
	if (m_damageSound.getSampleCount() == 0)
		m_damageSound.loadFromFile("Sounds/getHit.ogg");
	return m_damageSound;
}

//----------------------------------------------------------
sf::SoundBuffer & ResourceManager::getBoomerangSound()
{
	if (m_boomerangSound.getSampleCount() == 0)
	{
		m_boomerangSound.loadFromFile("Sounds/Boomer.ogg");
	}
	return m_boomerangSound;
}

//----------------------------------------------------------
sf::SoundBuffer & ResourceManager::getIntroductionSound()
{
	if (m_introductionSound.getSampleCount() == 0)
		m_introductionSound.loadFromFile("Sounds/Prologue.ogg");
	return m_introductionSound;
}

//----------------------------------------------------------
void ResourceManager::playLostLife()
{
	sf::Music lostLife;
	sf::Clock soundTimer;
	lostLife.openFromFile("Sounds/Life Lost.ogg");
	soundTimer.restart();
	lostLife.play();
	//while (soundTimer.getElapsedTime() < sf::seconds(2.5))
	while (lostLife.getStatus() == sf::SoundSource::Playing)
		continue;
}

//----------------------------------------------------------
std::string ResourceManager::getLevelMusicFile()
{
	return "Sounds/Level Music.ogg";
}

//----------------------------------------------------------
std::string ResourceManager::getEndGameMusicFile()
{
	return "Sounds/Stage Clear.ogg";
}

//----------------------------------------------------------
std::string ResourceManager::getBossFightMusicFile()
{
	return "Sounds/Boss Fight.ogg";
}

//----------------------------------------------------------
sf::Font & ResourceManager::getFont()
{
	static bool firstTimeLoad = false;
	if (!firstTimeLoad)
	{
		m_levelFont.loadFromFile("Font/8-BIT.ttf");
		firstTimeLoad = true;
	}
	return m_levelFont;
}
