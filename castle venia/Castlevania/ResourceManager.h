#pragma once
//- - - - - - - - - - - - include sectoin - - - - - - 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// - - - - - - - - - - - - - const section - - - - - -
const int INTRO_ANIMATION_LENGTH = 16;

class ResourceManager
{
public:
	ResourceManager();
	ResourceManager& operator=(const ResourceManager&) = default;
	~ResourceManager();

	sf::Texture& getPlayerTexture();
	sf::Texture& getEmptyTexture();
	sf::Texture& getDaggerTexture();
	sf::Texture& getAxeTexture();
	sf::Texture& getBoomerandTexture();
	sf::Texture& getZombieTexture();
	sf::Texture& getBatTexture();
	sf::Texture& getWolfTexture();
	sf::Texture& getMermanTexture();
	sf::Texture& getGiantBatTexture();
	sf::Texture& getCandleTexture();
	sf::Texture& getTorchTexture();
	sf::Texture& getBlockTexture();
	sf::Texture& getSHeartTexture();
	sf::Texture& getLHeartTexture();
	sf::Texture& getFoodTexture();
	sf::Texture& getWhipUpgradeTexture();
	sf::Texture& getFireballTexture();
	sf::Texture& getStageTexture(std::string filename);
	sf::Texture* getBackgroundSpritSheetTexture();
	sf::Texture& getBatIntroductionTexture();
	sf::Texture& getCloudTexture();
	sf::Texture& getTransitionWindowTexture();
	sf::SoundBuffer& getObjectHitSound();
	sf::SoundBuffer& getCollectHeartSound();
	sf::SoundBuffer& getCollectWeaponSound();
	sf::SoundBuffer& getCollectWhipUpgradeSound();
	sf::SoundBuffer& getThrowWeaponSound();
	sf::SoundBuffer& getWhipSound();
	sf::SoundBuffer& getDamageSound();
	sf::SoundBuffer& getBoomerangSound();
	sf::SoundBuffer& getIntroductionSound();
	void playLostLife();
	std::string getLevelMusicFile();
	std::string getEndGameMusicFile();
	std::string getBossFightMusicFile();
	sf::Font& getFont();
	void setNumOfBackgrounds(int num = 0) {m_stageTextures.resize(num); }

private:
	sf::Texture m_playerTexture;
	sf::Texture m_emptyTexture;
	sf::Texture m_daggerTexture;
	sf::Texture m_axeTexture;
	sf::Texture m_boomerangTexture;
	sf::Texture m_levelTexture;
	sf::Texture m_zombieTexture;
	sf::Texture m_batTexture;
	sf::Texture m_wolfTexture;
	sf::Texture m_mermanTexture;
	sf::Texture m_giantBatTexture;
	sf::Texture m_candleTexture;
	sf::Texture m_torchTexture;
	sf::Texture m_blockTexture;
	sf::Texture m_sHeartTexture;
	sf::Texture m_lHeartTexture;
	sf::Texture m_foodTexture;
	sf::Texture m_whipUpgradeTexture;
	sf::Texture m_fireballTexture;
	sf::Texture m_BatIntroduction;
	sf::Texture m_cloud;
	sf::Texture m_transitionWindow;
	sf::SoundBuffer m_objectHitSound;
	sf::SoundBuffer m_collectHeartSound;
	sf::SoundBuffer m_collectWeaponSound;
	sf::SoundBuffer m_collectWhipUpgradeSound;
	sf::SoundBuffer m_throwWeaponSound;
	sf::SoundBuffer m_whipSound;
	sf::SoundBuffer m_damageSound;
	sf::SoundBuffer m_boomerangSound;
	sf::SoundBuffer m_introductionSound;
	std::vector<sf::Texture> m_stageTextures;
	sf::Font m_levelFont;
	sf::Texture m_SpritSheetTexture[INTRO_ANIMATION_LENGTH];
};

