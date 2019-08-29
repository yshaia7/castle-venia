#include "Enemy.h"

//----------------------------------------------------------
Enemy::Enemy(sf::Vector2f startLocation, ResourceManager& rManager)
{
	setActive(false);
	m_direction = RIGHT;
	m_initialLocation = startLocation;
	setPosition(startLocation);
	m_spawnDistanceMax = 0;
	m_spawnDistanceMin = 0;
	setSoundBuffer(rManager.getObjectHitSound());
}

//----------------------------------------------------------
Enemy::~Enemy()
{
}

//----------------------------------------------------------
void Enemy::playerInteraction(std::weak_ptr<Player> player)
{
	if (player.expired())
		return;
	std::shared_ptr<Player> playerPTR = player.lock();
	float playerLocation = playerPTR->getHitbox().getPosition().x;

	//Set enemy as active when it's within a certain distance from the player
	if (!getActive() && abs(playerLocation - m_initialLocation.x) < m_spawnDistanceMax && (abs(playerLocation - m_initialLocation.x) > m_spawnDistanceMin))
	{
		move(playerLocation > m_initialLocation.x ? RIGHT : LEFT);
		spawnEnemy();
	}
	
	else if (getActive())
	{
		//Hit player if he touches an enemy
		if (playerPTR->collision(shared_from_this()) && !playerPTR->getDamagedState() && !getRemovalFlagState())
			playerPTR->getHit(shared_from_this());
		//Check if the player is hit by one of the enemy's projectiles
		for (auto i : m_attacks)
			if (playerPTR->collision(i) && !playerPTR->getDamagedState() && !getRemovalFlagState())
				playerPTR->getHit(shared_from_this());
		playerPTR->checkAttackTarget(shared_from_this());
		update();
		//Disable enemy when it's too far away
		if ( abs(playerLocation - m_hitbox.getPosition().x) > m_spawnDistanceMax || abs(playerPTR->getHitbox().getPosition().y - m_hitbox.getPosition().y) > 300)
		{
			m_attacks.clear();
			destroy();
		}
	}
}

//----------------------------------------------------------
void Enemy::spawnEnemy()
{
	setPosition(m_initialLocation);
	m_animationStage = 0;
	m_animationDelay = 0;
	setRemoveFlag(false);
	restoreHealth();
	setActive(true);
}

//----------------------------------------------------------
void Enemy::update()
{
	if (getRemovalFlagState())
	{
		m_attacks.clear();
		m_velocity.x = m_velocity.y = 0;
		if (m_animationDelay == ANIMATION_DELAY && m_animationStage == 3)
		{
			destroy();
			return;
		}
		loopingAnimation(3, m_hitbox.getGlobalBounds().width + 1, m_hitbox.getGlobalBounds().height + 1, m_hitbox.getGlobalBounds().height + 1);
	}
	Character::update();
}
