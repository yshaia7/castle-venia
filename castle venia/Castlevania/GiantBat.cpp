#include "GiantBat.h"


//----------------------------------------------------------
GiantBat::GiantBat(sf::Vector2f startLocation, ResourceManager& rManager, std::vector<int>bounds) : Enemy(startLocation, rManager)
{
	setTexture(rManager);
	setMaxHealth(MAX_HEALTH);
	restoreHealth();
	m_strength = STRENGTH;
	m_movementSpeed = MOVEMENT_SPEED;
	m_spawnDistanceMax = 70;
	setPosition(m_initialLocation);
	m_bounds = bounds;
	m_deathAnimationCounter = 0;
	m_points = 2500;
	m_timerStarted = false;
	m_flightAltitude = startLocation.y + 40;
}

//----------------------------------------------------------
GiantBat::~GiantBat()
{
}

//----------------------------------------------------------
void GiantBat::setTexture(ResourceManager & rManager)
{
	Object::setTexture(rManager.getGiantBatTexture());
	m_sprite.setTextureRect({ SPRITE_WIDTH * 2, 0, SPRITE_WIDTH, SPRITE_HEIGHT });
	m_hitbox.setSize(sf::Vector2f(m_sprite.getTextureRect().width, m_sprite.getTextureRect().height));
}

//----------------------------------------------------------
void GiantBat::playerInteraction(std::weak_ptr<Player> player)
{
	std::shared_ptr<Player> playerPTR = player.lock();
	float playerLocation = playerPTR->getHitbox().getGlobalBounds().left;

	//Reset boss' parameters before/after battle
	if (!getActive() && abs(playerLocation - m_initialLocation.x) > 200)
	{
		setPosition(m_initialLocation);
		m_isAttacking = false;
		m_midAttack = false;
		m_animationStage = 0;
		m_animationDelay = 0;
		m_sprite.setTextureRect({ SPRITE_WIDTH * 2, 0, SPRITE_WIDTH, SPRITE_HEIGHT });
	}

	//Mark boss' death
	if (playerPTR->getCameraLock() && !getActive() && m_deathAnimationCounter == DEATH_ANIMATION_LOOP)
	{
		playerPTR->setLevelClearState(true);
		m_deathAnimationCounter = 0;
		return;
	}

	//Spawn boss
	if (!getActive() && abs(playerLocation - m_initialLocation.x) < m_spawnDistanceMax && !playerPTR->getCameraLock())
	{
		m_battleStartTimer.restart();
		playerPTR->setCameraLock(true);
		m_timerStarted = true;
	}

	if (m_battleStartTimer.getElapsedTime() >= sf::seconds(2) && m_timerStarted)
	{
		m_direction = LEFT;
		spawnEnemy();
		m_attackTimer.restart();
		m_velocity = { 0,0 };
		m_timerStarted = false;
	}

	//Active boss actions
	else if (getActive())
	{
		float playerLocation = playerPTR->getHitbox().getGlobalBounds().left;
		if (playerPTR->collision(shared_from_this()) && !playerPTR->getDamagedState())
		{
			playerPTR->getHit(shared_from_this());
			if (playerPTR->getHealth() <= 0)
				setActive(false);
		}
		playerPTR->checkAttackTarget(shared_from_this());
		m_target = playerPTR->getHitbox().getPosition();
		update();
	}
}

//----------------------------------------------------------
void GiantBat::update()
{
	//Boss death animation
	if (getRemovalFlagState())
	{
		m_velocity.x = m_velocity.y = 0;
		if (m_animationDelay == ANIMATION_DELAY && m_animationStage == 3)
		{
			if (m_deathAnimationCounter < DEATH_ANIMATION_LOOP)
			{
				m_deathAnimationCounter++;
				m_animationDelay = 0;
				m_animationStage = 0;
			}
			else
				destroy();
		}
		loopingAnimation(3, m_hitbox.getGlobalBounds().width, m_hitbox.getGlobalBounds().height, m_hitbox.getGlobalBounds().height);
		return;
	}

	//Change direction when reached arena edges
	if (m_hitbox.getPosition().x + m_velocity.x > m_bounds[1] || (m_hitbox.getPosition().x + m_velocity.x < m_bounds[0]))
		m_direction = m_direction == LEFT ? RIGHT : LEFT;
	m_velocity.x = m_direction == RIGHT ? MOVEMENT_SPEED : -MOVEMENT_SPEED;

	if (!m_isAttacking)
	{
		m_velocity.y = cos((float)++m_flightArcCounter / FLIGHT_ARC_LIMITER);
		if (m_attackTimer.getElapsedTime() > sf::seconds(rand() % ATTACK_INTERVAL + 2) && abs(m_target.x - m_hitbox.getPosition().x) < 50)
		{
			m_midAttack = true;
			m_isAttacking = true;
			m_velocity.y = 0;
			m_direction = m_target.x > m_hitbox.getPosition().x ? RIGHT : LEFT;
		}
	}
	else
		swoop();
	rewindingAnimation(WALKING_FRAMES, SPRITE_WIDTH, SPRITE_HEIGHT, 0);

	Mobile::update();
}

//----------------------------------------------------------
void GiantBat::draw(sf::RenderWindow & window)
{
	if (m_deathAnimationCounter <= DEATH_ANIMATION_LOOP)
		window.draw(m_sprite);
}

//----------------------------------------------------------
void GiantBat::swoop()
{
	if (m_midAttack)
	{
		if (m_hitbox.getPosition().y + m_hitbox.getGlobalBounds().height > m_target.y + 35)
			m_midAttack = false;
		m_velocity.y = ATTACKING_SPEED;
	}
	else
	{
		if (m_hitbox.getPosition().y <= m_flightAltitude) {
			m_isAttacking = false;
			m_attackTimer.restart();
		}
		m_velocity.y = -ATTACKING_SPEED;
	}
}
