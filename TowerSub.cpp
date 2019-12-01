#include "TowerSub.h"
#include "Util\Math.h"
#include "ResourceManager\ResourceHolder.h"

// (1)window, (2)attack type, (3)strength
TowerSub::TowerSub(const sf::RenderWindow& window, attackType type, int strength) // this constructor gets called when tower is actually placed in m_towers in World.cpp
{
	storeLogicData(type, strength, sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window))));

	storeGraphicsData_TowerConstruction();
}

// TODO: fix the bug where a tower must wait for the cooldown time before attacking its first target
void TowerSub::update(std::vector<std::unique_ptr<Enemy>>* enemies)
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

void TowerSub::m_attackEnemies(std::vector<std::unique_ptr<Enemy>>* enemies)
{
	m_priority = targetPriority::close;
	m_numEnemiesToAttack = 1; //TODO: fix the bug: when there is more than one enemy in range with the same lowest health, and the tower
	// is ready to attack, the program crashes. have not tested yet for divide or root.
	std::vector<int> enemyIndices = {};

	for (unsigned int i_e = 0; i_e < enemies->size(); i_e++)
	{
		float enemyDistance = distanceBetweenPoints(enemies->at(i_e)->getPosition(), m_position);
		if (enemyDistance <= m_range) // if false, then enemy out of range, so skips the rest of the calculations for this enemy
		{
			if (enemies->at(i_e)->getHealth() > 0) /* ensure does not attack enemy of health 0, since that enemy will
				only be removed after all towers are done updating. NOTE: removing an enemy during tower updating would
				change the indices of all the enemies at later positions, which could cause towers with multiple targets
				to attack incorrectly */
			{
				enemyIndices = m_possiblyAddEnemyIndexToVectorAndSort(enemies, i_e, enemyIndices);
			}
		}
	}

	// this is the part of the function where we actually attack enemies
	if (enemyIndices.size() > 0) // we found (at least) one enemy to attack
	{
		m_bShouldResetElapsedTime = true;

		for (unsigned int i = 0; i < enemyIndices.size(); i++)
		{
			m_numofAttacksInWave++; // for stats purposes
			m_projectileManager.createProjectile(enemies->at(enemyIndices.at(i)), m_position, m_towerCircle.getFillColor());

			enemies->at(enemyIndices.at(i))->setHealth(enemies->at(enemyIndices.at(i))->getHealth() - m_strength);
		}
	}
}

