#include "TowerRoot.h"
#include "Util\Math.h"
#include "ResourceManager\ResourceHolder.h"

// (1)window, (2)attack type, (3)strength
TowerRoot::TowerRoot(const sf::RenderWindow& window, attackType type, int strength) // this constructor gets called when tower is actually placed in m_towers in World.cpp
{
	storeLogicData(type, strength, sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window))));

	storeGraphicsData_TowerConstruction();
}

void TowerRoot::update(std::vector<std::unique_ptr<Enemy>>* enemies)
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

void TowerRoot::m_attackEnemies(std::vector<std::unique_ptr<Enemy>>* enemies)
{
	m_priority = targetPriority::close;
	m_numEnemiesToAttack = 5;
	std::vector<int> enemyIndices = {};

	for (unsigned int i_e = 0; i_e < enemies->size(); i_e++)
	{
		float enemyDistance = distanceBetweenPoints(enemies->at(i_e)->getPosition(), m_position);
		if (enemyDistance <= m_range) // if false, then enemy out of range, so skips the rest of the calculations for this enemy
		{
			if (enemies->at(i_e)->getHealth() > 1) // ensure does not attack enemy of health 1 or 0
			{
				double val1 = std::round(std::pow(enemies->at(i_e)->getHealth(), 1. / double(m_strength)));
				double val2 = std::pow(enemies->at(i_e)->getHealth(), 1. / double(m_strength));

				if (abs(val1 - val2) < 1e-7) // is a perfect nth root
				{
					enemyIndices = m_possiblyAddEnemyIndexToVectorAndSort(enemies, i_e, enemyIndices);
				}
			}
		}
	}

	// this is the part of the function where we actually attack enemies

	if (enemyIndices.size() > 0) // we found (at least) one enemy to attack
	{
		m_bShouldResetElapsedTime = true;

		for (unsigned int i = 0; i < enemyIndices.size(); i++)
		{
			m_numofAttacksInWave++; // for stat collection purposes
			m_projectileManager.createProjectile(enemies->at(enemyIndices.at(i)), m_position, m_towerCircle.getFillColor());

			enemies->at(enemyIndices.at(i))->setHealth((int)std::pow(enemies->at(enemyIndices.at(i))->getHealth(), 1. / double(m_strength)));
		}
	}
}

