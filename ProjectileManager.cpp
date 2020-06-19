#include "ProjectileManager.h"

ProjectileManager::ProjectileManager()
{
	m_defaultProjSpeed = 8.f;
}

void ProjectileManager::update(std::vector<std::unique_ptr<Enemy>>* enemies)
{
	for (unsigned int i = 0; i < m_projectiles.size(); i++)
	{
		if (m_projectiles.at(i)->getPosition() == m_projectiles.at(i)->getEndPos())
		{
			for (unsigned int e = 0; e < enemies->size(); e++) // find the enemy to attack
			{
				if (enemies->at(e)->getStaticIndex() == m_projectiles.at(i)->getEnemyStaticIndex())
				{
					// then attack this enemy
					switch (m_projectiles.at(i)->getTowerAttackType())
					{
					case attackType::root:
					{
						enemies->at(e)->setHealth((int)std::round(std::pow(enemies->at(e)->getHealth(), 1. / float(m_projectiles.at(i)->getTowerAttackStrength()))));
						break;
					}
					case attackType::divide:
					{
						enemies->at(e)->setHealth(enemies->at(e)->getHealth() / m_projectiles.at(i)->getTowerAttackStrength());
						break;
					}
					case attackType::subtract:
					{
						enemies->at(e)->setHealth(enemies->at(e)->getHealth() - m_projectiles.at(i)->getTowerAttackStrength());
						// TODO: change enemy colour temporarily to match projectile colour --
						// also allow other temporary changes to the enemy's properties, such as speed
						// (should this happen in Enemy.cpp? should the changing of health even happen there too?)
						break;
					}
					}
				}
			}

			m_projectiles.erase(m_projectiles.begin() + i);
		}
	}

	for (auto& proj : m_projectiles)
	{
		proj->update();
	}
	
}

void ProjectileManager::render(sf::RenderTarget& renderer)
{
	for (auto& proj : m_projectiles)
	{
		proj->render(renderer);
	}
}

/*Calculates the start and end positions of the projectile, as well as projectile appearance, based on arguments passed. */
void ProjectileManager::createProjectile(
	const std::unique_ptr<Enemy>& enemy, sf::Vector2f towPos, attackType towAttackType, int towAttackStrength, sf::Color towColour, float towRadius, int towNumPts)
	/* create projectile with the appropriate properties, including end position of travel.
	-- the time for the proj to get to the OG position of enemy is (OG distance)/(proj speed).
	-- the distance the enemy travels in this time is (enemy speed) * (OG distance)/(proj speed);
	normally we will aim the projectile at a point this distance ahead of the enemy (called endPos).
	-- if the enemy is close to its next vertex (less than the distance referred to above), then
	we simply shoot at the vertex
	*/
{
	sf::Vector2f endPos;

	float speedRatio = enemy->getSpeed() / m_defaultProjSpeed;
	float OGdistanceTowerToEnemy = distanceBetweenPoints(towPos, enemy->getPosition());

	if (distanceBetweenPoints(enemy->getPosition(), enemy->getNextDest()) < speedRatio * OGdistanceTowerToEnemy)
	{
		endPos = enemy->getNextDest();
		// if the enemy will pass the dest before the projectile arrives, just shoot at the dest as an approximation
	}
	else
	{
		endPos = {
		enemy->getPosition().x + speedRatio * OGdistanceTowerToEnemy * cosf(enemy->getTheta()),
		enemy->getPosition().y + speedRatio * OGdistanceTowerToEnemy * sinf(enemy->getTheta())
		};
	}
	
	// TODO: make the enemy being attacked match the colour for a brief moment of the
	// projectile that attacks it (which could also match the colour of the attacking
	// tower?  This would make it more clear which enemies are being attacked by which towers
	m_projectiles.push_back(std::make_unique<Projectile>(
		towPos, endPos, m_defaultProjSpeed, enemy->getStaticIndex()
		, towAttackType, towAttackStrength, towColour, towRadius, towNumPts));

}


