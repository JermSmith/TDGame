#include "TowerRoot.h"
#include "Util\Math.h"
#include "ResourceManager\ResourceHolder.h"

// (1)attack type, (2)strength, (3)position
TowerRoot::TowerRoot(const attackType& type, const int& strength, const sf::Vector2f& position, const float& radius)
// this constructor gets called when tower is actually placed in m_towers in TowerManager.cpp
{
	setBasicProperties(type, strength, position, radius);

	if (m_strength == 2)
	{
		m_strengthString.setString("Sqrt");
	}
	else if (m_strength == 3)
	{
		m_strengthString.setString("Cbrt");
	}
	else
	{
		m_strengthString.setString(std::to_string(m_strength) + "th root");
	}
}

void TowerRoot::updateAttackLogic(std::vector<std::unique_ptr<Enemy>>* enemies)
{
	m_timeElapsedSinceAttack = m_timer.getElapsedTime() - m_timeOfLastAttack;

	if (m_timeElapsedSinceAttack > m_cooldownTime)
	{
		// projectiles also created in this function
		m_attackEnemies(enemies);

		if (m_bShouldResetElapsedTime) // essentially reset m_elapsedTime to 0 (see above)
		{
			m_timeOfLastAttack = m_timer.getElapsedTime();
			m_bShouldResetElapsedTime = false;
		}
	}
}

void TowerRoot::m_attackEnemies(std::vector<std::unique_ptr<Enemy>>* enemies)
{
	std::vector<int> enemyIndicesToAttack = {};

	for (unsigned int i_e = 0; i_e < enemies->size(); i_e++)
	{
		float enemyDistance = distanceBetweenPoints(enemies->at(i_e)->getPosition(), m_position);
		if (enemyDistance < m_range) // if false, then enemy out of range, so skips the rest of the calculations for this enemy
		{
			if (enemies->at(i_e)->getHealth() > 1) // ensure does not attack enemy of health 1 or 0
			{
				double val1 = std::round(std::pow(enemies->at(i_e)->getHealth(), 1. / double(m_strength)));
				double val2 = std::pow(enemies->at(i_e)->getHealth(), 1. / double(m_strength));

				if (abs(val1 - val2) < 1e-7) // is a perfect nth root
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
			m_numofAttacksInWave++; // for wave stats
			m_projectileManager.createProjectile(enemies->at(enemyIndicesToAttack.at(i)), m_position, InteractableShape::getFillColour());

			enemies->at(enemyIndicesToAttack.at(i))->setHealth((int)std::round(std::pow(enemies->at(enemyIndicesToAttack.at(i))->getHealth(), 1. / float(m_strength))));
		}
	}
}


