#include "TowerSub.h"
#include "Util\Math.h"
#include "ResourceManager\ResourceHolder.h"

// TODO: implement upgrade system
// idea for +1 tower:
// basic level: gives enemies +2 health, but slows them for some time
// first upgrade: only gives enemies +1 health, and slows enemies to a greater extent for a longer time
// second upgrade: still gives enemies +1 health, but slows enemies almost to a stop for some time
// (could possibly split these upgrades up over more upgrades, like 3 or 4 levels of upgrades?)

// (1)attack type, (2)strength, (3)position
TowerSub::TowerSub(const attackType& type, const int& strength, const sf::Vector2f& position, const float& radius, const int& pointCount)
// this constructor gets called when tower is actually placed in m_towers in TowerManager.cpp
{
	setBasicProperties(type, strength, position, radius, pointCount);

	if (m_strength < 0) { m_strengthString.setString("+ " + std::to_string(m_strength)); }
	else { m_strengthString.setString("- " + std::to_string(m_strength)); }
}

void TowerSub::updateAtakTimer_FindEnems_CreateProj(const std::vector<std::unique_ptr<Enemy>>& enemies)
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
				if (enemies.at(i_e)->getHealth() > 0) /* ensure does not attack enemy of health 0, since that enemy will
					only be removed after all towers are done updating. NOTE: removing an enemy during tower updating would
					change the indices of all the enemies at later positions, which could cause towers with multiple targets
					to attack incorrectly.
					TODO: possibly reconsider this, since now enemies have static indices. When generating enemyIndicesToAttack,
					can store their static index, not their index in "m_enemies" */
				{
					enemyIndicesToAttack = m_possiblyAddEnemyIndexToVectorAndSort(enemies, i_e, enemyIndicesToAttack);
				}
			}
		}

		if (enemyIndicesToAttack.size() > 0) // we found at least one enemy to attack
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


