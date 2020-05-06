#include "TowerSub.h"
#include "Util\Math.h"
#include "ResourceManager\ResourceHolder.h"

#include <iostream>

// (1)attack type, (2)strength, (3)position
TowerSub::TowerSub(const attackType& type, const int& strength, const sf::Vector2f& position) // this constructor gets called when tower is actually placed in m_towers in World.cpp
{
	setBasicProperties(type, strength, position);

	m_cooldownTime = sf::milliseconds(1000);
	m_priority = targetPriority::largestPrime;
	m_maxNumTargets = 2;

	if (m_strength < 0) { m_strengthString.setString("+ " + std::to_string(m_strength)); }
	else { m_strengthString.setString("- " + std::to_string(m_strength)); }
}

void TowerSub::update(std::vector<std::unique_ptr<Enemy>>* enemies, const sf::RenderWindow& window)
{
	m_elapsedTime = m_timer.getElapsedTime() - m_timePoint;

	if (m_elapsedTime > m_cooldownTime)
	{
		// projectiles also created in this function
		m_attackEnemies(enemies);

		if (m_bShouldResetElapsedTime) // essentially reset m_elapsedTime to 0 (see above)
		{
			m_timePoint = m_timer.getElapsedTime();
			m_bShouldResetElapsedTime = false;
		}
	}

	m_projectileManager.update();

	if (m_bIsClickedOn)
	{
		m_rangeCircle.setFillColor(sf::Color(255, 255, 255, 63));
		InteractableShape::setClickedAppearance();
	}
	else
	{
		m_rangeCircle.setFillColor(sf::Color::Transparent);
		InteractableShape::removeClickedAppearance();
	}

	if (isRolledOn(window))
	{
		InteractableShape::setRolledAppearance();
	}
	else if (!m_bIsClickedOn)
	{
		InteractableShape::removeRolledAppearance();
	}
}

void TowerSub::m_attackEnemies(std::vector<std::unique_ptr<Enemy>>* enemies)
{
	std::vector<int> enemyIndicesToAttack = {};

	for (unsigned int i_e = 0; i_e < enemies->size(); i_e++)
	{
		float enemyDistance = distanceBetweenPoints(enemies->at(i_e)->getPosition(), m_position);
		if (enemyDistance < m_range) // if false, then enemy out of range, so skips the rest of the calculations for this enemy
		{
			if (enemies->at(i_e)->getHealth() > 0) /* ensure does not attack enemy of health 0, since that enemy will
				only be removed after all towers are done updating. NOTE: removing an enemy during tower updating would
				change the indices of all the enemies at later positions, which could cause towers with multiple targets
				to attack incorrectly */
			{
				enemyIndicesToAttack = m_possiblyAddEnemyIndexToVectorAndSort(enemies, i_e, enemyIndicesToAttack);
			}
		}
	}

	// this is the part of the function where we actually attack enemies
	if (enemyIndicesToAttack.size() > 0) // we found (at least) one enemy to attack
	{
		m_bShouldResetElapsedTime = true;

		for (unsigned int i = 0; i < enemyIndicesToAttack.size(); i++)
		{
			m_numofAttacksInWave++; // for wave stats
			m_projectileManager.createProjectile(enemies->at(enemyIndicesToAttack.at(i)), m_position, InteractableShape::getFillColour());

			enemies->at(enemyIndicesToAttack.at(i))->setHealth(enemies->at(enemyIndicesToAttack.at(i))->getHealth() - m_strength);
			// TODO: fix the horrid "get enemies" function in WorldManager by changing the way enemy health is decreased:
			// do not decrease health when a projectile is fired, but rather when the projectile reaches the enemy:
			// when updating enemies (in Enemy.cpp), check if a projectile has arrived, and if so, modify the enemy health
			// This could be challenging b/c all ProjectileManagers are currently owned by each individual Tower, but
			// this may possibly be overcome by making towermanager a friend of a bunch of classes?? or something??
		}
	}
}


