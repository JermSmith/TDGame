#include "TowerDiv.h"
#include "Util\Math.h"
#include "ResourceManager\ResourceHolder.h"

// (1)window, (2)attack type, (3)strength[int], (4)position[sf::Vector2f], (5)radius[float], (6)pointCount[int]
TowerDiv::TowerDiv(const sf::RenderWindow& window, const attackType& type, int strength, const sf::Vector2f& position
	, float radius, int pointCount)
	:
	Tower(window, type, strength, position, radius, pointCount)
{
	generateHoverWidgets(window);
	generateUpgradeWidgets(window);
	generatePriorityWidgets(window);
	generateStatsWidgets(window);
}
// this constructor gets called when tower is actually placed in m_towers in TowerManager.cpp

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
				m_lifetimeNumProjFired++; // for wave stats // TODO: add more stat collection here
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

void TowerDiv::generateHoverWidgets(const sf::RenderWindow& window)
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
		bnrPriority.setText("Error: Priority Largest Prime"); // should never happen for root or div tower
		break;

	default:
		bnrPriority.setText("Priority: Error");
		break;
	}
}

void TowerDiv::generateUpgradeWidgets(const sf::RenderWindow& window)
{
	// UPGRADE MENU

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

	btnSetPriority.setText("Set Target Priority");
	btnSetPriority.setFunction([&]()
		{
			if (m_statsMenu.bContainsWidgets())
			{
				m_statsMenu.hide();
				populatePriorityMenu();
			}
			else
			{
				m_priorityMenu.hide();
				populateStatsMenu();
			}
		});
}

void TowerDiv::generatePriorityWidgets(const sf::RenderWindow& window)
{
	// PRIORITY MENU

	btnPriClose.setText("Closest");
	btnPriClose.setFunction([&]()
		{
			m_priority = targetPriority::close;
			generateHoverWidgets(window);
			m_priorityMenu.hide();
			populateStatsMenu();
		});

	btnPriFirst.setText("First");
	btnPriFirst.setFunction([&]()
		{
			m_priority = targetPriority::first;
			generateHoverWidgets(window);
			m_priorityMenu.hide();
			populateStatsMenu();
		});

	btnPriLast.setText("Last");
	btnPriLast.setFunction([&]()
		{
			m_priority = targetPriority::last;
			generateHoverWidgets(window);
			m_priorityMenu.hide();
			populateStatsMenu();
		});

	btnPriStrong.setText("Strongest");
	btnPriStrong.setFunction([&]()
		{
			m_priority = targetPriority::strong;
			generateHoverWidgets(window);
			m_priorityMenu.hide();
			populateStatsMenu();
		});

	btnPriWeak.setText("Weakest");
	btnPriWeak.setFunction([&]()
		{
			m_priority = targetPriority::weak;
			generateHoverWidgets(window);
			m_priorityMenu.hide();
			populateStatsMenu();
		});

	// largest prime priority only for sub tower
}

void TowerDiv::generateStatsWidgets(const sf::RenderWindow& window)
{
	// STATS MENU

	bnrLastWaveNumProj.setText("# projectiles (last wave): " + std::to_string(m_lastWaveNumProjFired));
	bnrLifetimeNumProj.setText("# projectiles (lifetime): " + std::to_string(m_lifetimeNumProjFired));

	bnrLastWaveDmg.setText("# projectiles (last wave): " + std::to_string(m_lastWaveDmg));
	bnrLifetimeDmg.setText("# projectiles (lifetime): " + std::to_string(m_lifetimeDmg));
}

void TowerDiv::populateHoverMenu()
{
	m_hoverMenu.addWidget(bnrRange);
	m_hoverMenu.addWidget(bnrCooldown);
	m_hoverMenu.addWidget(bnrProjSpeed);
	m_hoverMenu.addWidget(bnrNumTargets);
	m_hoverMenu.addWidget(bnrPriority);

	m_hoverMenu.showOutline();
}

void TowerDiv::populateUpgradeMenu()
{
	m_upgradeMenu.addWidget(btnUpgrade1);
	m_upgradeMenu.addWidget(btnUpgrade2);
	m_upgradeMenu.addWidget(btnUpgrade3);
	m_upgradeMenu.addWidget(btnUpgrade4);
	m_upgradeMenu.addWidget(btnSetPriority);

	m_upgradeMenu.showOutline();
}

void TowerDiv::populatePriorityMenu()
{
	m_priorityMenu.addWidget(btnPriClose);
	m_priorityMenu.addWidget(btnPriFirst);
	m_priorityMenu.addWidget(btnPriLast);
	m_priorityMenu.addWidget(btnPriStrong);
	m_priorityMenu.addWidget(btnPriWeak);

	m_priorityMenu.showOutline();
}

void TowerDiv::populateStatsMenu()
{
	m_statsMenu.addWidget(bnrLastWaveNumProj);
	m_statsMenu.addWidget(bnrLifetimeNumProj);

	m_statsMenu.addWidget(bnrLastWaveDmg);
	m_statsMenu.addWidget(bnrLifetimeDmg);

	m_statsMenu.showOutline();
}




