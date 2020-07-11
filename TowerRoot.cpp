#include "TowerRoot.h"
#include "Util\Math.h"
#include "ResourceManager\ResourceHolder.h"

// TODO: implement ROOT tower upgrades:
// basic level: single-shot attack
// first upgrade: multi-shot attack
// second upgrade: insta-root when enemy comes in range

// other upgrades: range, rate of fire, **projectile speed** (perhaps the most important upgrade for every tower)
// perhaps the ability to prioritize different targets can also be an upgrade??

// (1)window, (2)attack type, (3)strength[int], (4)position[sf::Vector2f], (5)radius[float], (6)pointCount[int]
TowerRoot::TowerRoot(const sf::RenderWindow& window, const attackType& type, int strength, const sf::Vector2f& position
	, float radius, int pointCount)
	:
	Tower(window, type, strength, position, radius, pointCount)
{
	generateWidgets(window);
}
	// this constructor gets called when tower is actually placed in m_towers in TowerManager.cpp

void TowerRoot::updateAtakTimer_FindEnems_CreateProj(const std::vector<std::unique_ptr<Enemy>>& enemies)
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
					double val1 = std::round(std::pow(enemies.at(i_e)->getHealth(), 1. / double(m_strength)));
					double val2 = std::pow(enemies.at(i_e)->getHealth(), 1. / double(m_strength));

					if (abs(val1 - val2) < 1e-7) // is a perfect nth root
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

void TowerRoot::generateWidgets(const sf::RenderWindow& window)
{
	// HOVER MENU

	bnrRange.setText("Range: " + roundToString(m_range, 1));
	bnrCooldown.setText("Cooldown: " + roundToString(m_cooldownTime.asSeconds(), 2));
	bnrProjSpeed.setText("Proj.speed: " + roundToString(m_projSpeed, 2));
	bnrNumTargets.setText("# targets: " + roundToString(m_maxNumTargets, 0));
	switch (m_priority)
	{
	case targetPriority::close:
		bnrPriority.setText("Priority: Close");
		break;

	case targetPriority::first:
		bnrPriority.setText("Priority: First");
		break;

	case targetPriority::last:
		bnrPriority.setText("Priority: Last");
		break;

	case targetPriority::strong:
		bnrPriority.setText("Priority: Strongest");
		break;

	case targetPriority::weak:
		bnrPriority.setText("Priority: Weakest");
		break;

	case targetPriority::largestPrime:
		bnrPriority.setText("Priority: Largest Prime");
		break;

	default:
		bnrPriority.setText("Priority: Error");
		break;
	}

	// STATS MENU

	btnUpgrade1.setText("Upgrade 1");
	btnUpgrade1.setFunction([&]()
		{

		});

	btnUpgrade2.setText("Upgrade 2");
	btnUpgrade2.setFunction([&]()
		{

		});

	btnUpgrade3.setText("Upgrade 3");
	btnUpgrade3.setFunction([&]()
		{

		});

	btnUpgrade4.setText("Upgrade 4");
	btnUpgrade4.setFunction([&]()
		{

		});
}

void TowerRoot::populateHoverMenu()
{
	m_hoverMenu.addWidget(bnrRange);
	m_hoverMenu.addWidget(bnrCooldown);
	m_hoverMenu.addWidget(bnrProjSpeed);
	m_hoverMenu.addWidget(bnrNumTargets);
	m_hoverMenu.addWidget(bnrPriority);

	m_hoverMenu.showOutline();
}

void TowerRoot::populateStatsMenu()
{
	m_statsMenu.addWidget(btnUpgrade1);
	m_statsMenu.addWidget(btnUpgrade2);
	m_statsMenu.addWidget(btnUpgrade3);
	m_statsMenu.addWidget(btnUpgrade4);

	m_statsMenu.showOutline();
}



