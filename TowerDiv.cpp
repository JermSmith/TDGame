#include "TowerDiv.h"
#include "Util\Math.h"
#include "ResourceManager\ResourceHolder.h"

// (1)attack type, (2)strength, (3)position
TowerDiv::TowerDiv(const attackType& type, const int& strength, const sf::Vector2f& position) // this constructor gets called when tower is actually placed in m_towers in World.cpp
{
	setBasicProperties(type, strength, position);

	m_cooldownTime = sf::milliseconds(1000);
	m_priority = targetPriority::strong;
	m_maxNumTargets = 2;

	//m_towerCircle.setFillColor(sf::Color::Cyan);
	//m_rangeCircle.setFillColor(sf::Color(255, 255, 255, 63));
	//m_strengthString.setFillColor(sf::Color::Red);
	m_strengthString.setString("/ " + std::to_string(m_strength));
}

void TowerDiv::update(std::vector<std::unique_ptr<Enemy>>* enemies)
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

	if (m_bIsClickedOn)
	{
		m_rangeCircle.setFillColor(sf::Color(255, 255, 255, 63));
	}
	else { m_rangeCircle.setFillColor(sf::Color::Transparent); }

	m_projectileManager.update();

}

void TowerDiv::m_attackEnemies(std::vector<std::unique_ptr<Enemy>>* enemies)
{
	std::vector<int> enemyIndicesToAttack = {};

	for (unsigned int i_e = 0; i_e < enemies->size(); i_e++)
	{
		float enemyDistance = distanceBetweenPoints(enemies->at(i_e)->getPosition(), m_position);
		if (enemyDistance < m_range) // if false, then enemy out of range, so skips the rest of the calculations for this enemy
		{
			if (enemies->at(i_e)->getHealth() > 1) // ensure does not attack enemy of health 1 or 0
			{
				if (enemies->at(i_e)->getHealth() % m_strength == 0) // if false, then enemy health not divisible by m_strength
				{
					enemyIndicesToAttack = m_possiblyAddEnemyIndexToVectorAndSort(enemies, i_e, enemyIndicesToAttack);
				}
			}
		}
	}

	// this is the part of the function where we actually attack enemies
	if (enemyIndicesToAttack.size() > 0) // we found (at least) one enemy to attack
	{
		m_bShouldResetElapsedTime = true;

		for (unsigned int i = 0; i < enemyIndicesToAttack.size(); i++)
		{
			m_numofAttacksInWave++; // for stat collection purposes
			m_projectileManager.createProjectile(enemies->at(enemyIndicesToAttack.at(i)), m_position, m_towerCircle.getFillColor());

			enemies->at(enemyIndicesToAttack.at(i))->setHealth(enemies->at(enemyIndicesToAttack.at(i))->getHealth() / m_strength);
		}
	}
}

