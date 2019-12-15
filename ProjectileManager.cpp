#include "ProjectileManager.h"

ProjectileManager::ProjectileManager()
{
	m_defaultProjSpeed = 10.f;
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
	}
	else
	{
		endPos = {
		enemy->getPosition().x + speedRatio * OGdistanceTowerToEnemy * cosf(enemy->getTheta()),
		enemy->getPosition().y + speedRatio * OGdistanceTowerToEnemy * sinf(enemy->getTheta())
		};
	}
	
	m_projectiles.push_back(std::make_unique<Projectile>(towerPos, endPos, m_defaultProjSpeed, colour));

}

