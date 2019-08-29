#include "Character.h"


//----------------------------------------------------------
Character::Character()
{
	m_isMoving = false;
	m_isAttacking = false;
	m_isInvincible = false;
	m_animationDirection = RIGHT;
	m_animationDelay = 0;
	m_animationStage = -1;
}

//----------------------------------------------------------
Character::~Character()
{
}

//----------------------------------------------------------
void Character::update()
{

	//Remove character after its' death animation is over
	if (getRemovalFlagState())
	{
		m_velocity.x = m_velocity.y = 0;
		if (m_animationDelay == ANIMATION_DELAY && m_animationStage == 3)
		{
			destroy();
			return;
		}
		loopingAnimation(3, m_hitbox.getGlobalBounds().width + 1, m_hitbox.getGlobalBounds().height + 1, m_hitbox.getGlobalBounds().height + 1);
	}

	//Update state of characters' weapons
	for (int i = 0; i < m_attacks.size(); i++)
	{
		m_attacks[i]->update();

		//Delete weapon if it's too far away from the character who called it
		if (abs(m_attacks[i]->getHitbox().getGlobalBounds().left - m_hitbox.getGlobalBounds().left) >= 250 || abs(m_attacks[i]->getHitbox().getGlobalBounds().height - m_hitbox.getGlobalBounds().height) >= 200 || 
																						     m_attacks[i]->getHitbox().getGlobalBounds().top - m_hitbox.getGlobalBounds().top >= 120 || !m_attacks[i]->getActive())
			m_attacks.erase(m_attacks.begin() + i);
	}


	Mobile::update();
}

//----------------------------------------------------------
void Character::move(DIRECTION direction)
{
	if (m_direction != direction)
	{
		flip(direction);
		m_direction = direction;
	}
}

//----------------------------------------------------------
void Character::jump()
{
	//Can't jump while already in the air
	if (!m_falling)
	{
		m_falling = true;
		m_velocity.y = -m_jumpingHeight;
	}
}

//----------------------------------------------------------
void Character::attack(std::shared_ptr<Weapon> weapon)
{
	m_attacks.push_back(weapon);
}

//----------------------------------------------------------
void Character::getHit(std::weak_ptr<Character> hitChar)
{
	if (hitChar.expired())
		return;
	m_health -= hitChar.lock()->getStrength();
	//Kill character
	if (m_health <= 0)
	{
		m_animationDelay = m_animationStage = 0;
		setRemoveFlag(true);
	}
}

//----------------------------------------------------------
void Character::draw(sf::RenderWindow& window)
{
	Object::draw(window);
	for (auto i : m_attacks)
		i->draw(window);
}

//----------------------------------------------------------
void Character::flip(DIRECTION direction)
{
	if (direction == RIGHT)
		m_sprite.setOrigin({ 0, 0 });
	else
		m_sprite.setOrigin({ m_hitbox.getGlobalBounds().width, 0 });
	m_sprite.scale(-1, 1);
}

//----------------------------------------------------------
void Character::rewindingAnimation(int numOfFrames, int spriteWidth, int spriteHeight, int spriteY)
{
	//Only advance animation once per several frames
	if (m_animationDelay != ANIMATION_DELAY)
	{
		m_animationDelay++;
		return;
	}
	if (m_animationDirection == RIGHT)
	{
		if (m_animationStage < 0)
			m_animationStage++;
		m_sprite.setTextureRect({ spriteWidth * m_animationStage, spriteY, spriteWidth, spriteHeight });
		m_animationDelay = 0;
		m_animationStage++;
		if (m_animationStage == numOfFrames)
		{
			m_animationDirection = LEFT;
			return;
		}
	}
	else
	{
		if (m_animationStage >= numOfFrames)
			m_animationStage--;
		m_sprite.setTextureRect({ spriteWidth * m_animationStage, spriteY, spriteWidth, spriteHeight });
		m_animationDelay = 0;
		m_animationStage--;
		if (m_animationStage == -1)
		{
			m_animationDirection = RIGHT;
			return;
		}
	}
}
