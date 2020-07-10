#include "TowerDiv.h"
#include "Util\Math.h"
#include "ResourceManager\ResourceHolder.h"

// (1)attack type, (2)strength, (3)position
TowerDiv::TowerDiv(const attackType& type, const int& strength, const sf::Vector2f& position, const float& radius, const int& pointCount)
// this constructor gets called when tower is actually placed in m_towers in TowerManager.cpp
{
	setBasicProperties(type, strength, position, radius, pointCount);

	m_strengthString.setString("/ " + std::to_string(m_strength));
}

void TowerDiv::updateAtakTimer_FindEnems_CreateProj(const std::vector<std::unique_ptr<Enemy>>& enemies)
{
	m_timeElapsedSinceAttack = m_timer.getElapsedTime() - m_timeOfLastAttack;

	if (m_timeElapsedSinceAttack > m_cooldownTime)
	{
		std::vector<int> enemyIndicesToAttack = {};

		for (unsigned int i_e = 0; i_e < enemies.size(); i_e++)
		{
			float enemyDistance = distanceBetweenPoints(enemies.at(i_e)->getPosition(), m_position);
			if (enemyDistance < m_range) // if false, then enemy out of range, so skips the rest of the calculations for this enemy
			{
				if (enemies.at(i_e)->getHealth() > 1) // ensure does not attack enemy of health 1 or 0
				{
					if (enemies.at(i_e)->getHealth() % m_strength == 0) // if false, then enemy health not divisible by m_strength
					{
						enemyIndicesToAttack = m_possiblyAddEnemyIndexToVectorAndSort(enemies, i_e, enemyIndicesToAttack);
					}
				}
			}
		}

		if (enemyIndicesToAttack.size() > 0) // we found (at least) one enemy to attack
		{
			m_bShouldResetElapsedTime = true;

			for (unsigned int i = 0; i < enemyIndicesToAttack.size(); i++)
			{
				m_numofAttacksInWave++; // for wave stats
				m_projectileManager.createProjectile
				(enemies.at(enemyIndicesToAttack.at(i))
					, m_position
					, m_attackType
					, m_strength
					, m_projSpeed
					, InteractableShape::getFillColour()
					, InteractableShape::getPrimaryDim()
					, InteractableShape::getPointCount());
			}
		}

		if (m_bShouldResetElapsedTime) // essentially reset m_elapsedTime to 0 (see above)
		{
			m_timeOfLastAttack = m_timer.getElapsedTime();
			m_bShouldResetElapsedTime = false;
		}
	}
}



