#include "ProjectileManager.h"

ProjectileManager::ProjectileManager()
{
	m_defaultProjSpeed = 5.f; // TODO: fix the problem where div and root towers shoot super fast projectiles, since they need to shoot the enemy before the sub towers shoot
}

void ProjectileManager::update()
{
	for (unsigned int i = 0; i < m_projectiles.size(); i++)
	{
		if (m_projectiles.at(i)->getPosition() == m_projectiles.at(i)->getEndPos())
		{
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

void ProjectileManager::createProjectile(const std::unique_ptr<Enemy>& enemy, sf::Vector2f towerPos, sf::Color colour)
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
	float OGdistanceTowerToEnemy = distanceBetweenPoints(towerPos, enemy->getPosition());

	if (distanceBetweenPoints(enemy->getPosition(), enemy->getNextDest()) < speedRatio * OGdistanceTowerToEnemy)
	{
		endPos = enemy->getNextDest();
		// if the enemy will pass the dest before the projectile arrives, just shoot at the dest (this is just for looks anyways)
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
	m_projectiles.push_back(std::make_unique<Projectile>(towerPos, endPos, m_defaultProjSpeed, colour));

}


