#include "TowerSub.h"
#include "Util\Math.h"
#include "ResourceManager\ResourceHolder.h"

// TODO: implement upgrade system
// idea for +1 tower:
// basic level: gives enemies +2 health, but slows them for some time
// first upgrade: only gives enemies +1 health, and slows enemies to a greater extent for a longer time
// second upgrade: still gives enemies +1 health, but slows enemies almost to a stop for some time
// (could possibly split these upgrades up over more upgrades, like 3 or 4 levels of upgrades?)

// (1)window, (2)attack type, (3)strength[int], (4)position[sf::Vector2f], (5)radius[float], (6)pointCount[int]
TowerSub::TowerSub(const sf::RenderWindow& window, const attackType& type, int strength, const sf::Vector2f& position
	, float radius, int pointCount)
	:
	Tower(window, type, strength, position, radius, pointCount)
{
	generateWidgets(window);
}
// this constructor gets called when tower is actually placed in m_towers in TowerManager.cpp

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

void TowerSub::generateWidgets(const sf::RenderWindow& window)
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
			// reveal priority menu, hide stats menu
		});

	// PRIORITY MENU

	btnPriClose.setText("Closest");
	btnPriClose.setFunction([&]()
		{
			m_priority = targetPriority::close;
		});

	btnPriFirst.setText("First");
	btnPriFirst.setFunction([&]()
		{
			m_priority = targetPriority::first;
		});

	btnPriLast.setText("Last");
	btnPriLast.setFunction([&]()
		{
			m_priority = targetPriority::last;
		});

	btnPriStrong.setText("Strongest");
	btnPriStrong.setFunction([&]()
		{
			m_priority = targetPriority::strong;
		});

	btnPriWeak.setText("Weakest");
	btnPriWeak.setFunction([&]()
		{
			m_priority = targetPriority::weak;
		});

	btnPriLgPrime.setText("Largest Prime");
	btnPriLgPrime.setFunction([&]()
		{
			m_priority = targetPriority::largestPrime;
		});

	// STATS MENU

	bnrLastWaveNumProj.setText("# projectiles (last wave): " + std::to_string(m_lastWaveNumProjFired));
	bnrLifetimeNumProj.setText("# projectiles (lifetime): " + std::to_string(m_lifetimeNumProjFired));

	bnrLastWaveDmg.setText("# projectiles (last wave): " + std::to_string(m_lastWaveDmg));
	bnrLifetimeDmg.setText("# projectiles (lifetime): " + std::to_string(m_lifetimeDmg));

	bnrLastWaveKills.setText("# kills (last wave): " + std::to_string(m_lastWaveDmg));
	bnrLifetimeKills.setText("# kills (lifetime): " + std::to_string(m_lifetimeDmg));


}

void TowerSub::populateHoverMenu()
{
	m_hoverMenu.addWidget(bnrRange);
	m_hoverMenu.addWidget(bnrCooldown);
	m_hoverMenu.addWidget(bnrProjSpeed);
	m_hoverMenu.addWidget(bnrNumTargets);
	m_hoverMenu.addWidget(bnrPriority);

	m_hoverMenu.showOutline();
}

void TowerSub::populateUpgradeMenu()
{
	m_upgradeMenu.addWidget(btnUpgrade1);
	m_upgradeMenu.addWidget(btnUpgrade2);
	m_upgradeMenu.addWidget(btnUpgrade3);
	m_upgradeMenu.addWidget(btnUpgrade4);
	m_upgradeMenu.addWidget(btnSetPriority);

	m_upgradeMenu.showOutline();
}




