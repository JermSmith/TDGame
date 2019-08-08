#include "World.h"

#include "Util\Math.h"
#include "Path.h"

World::World()
{
	
}

void World::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
	// TODO: pass this along to tower.handleEvent(e, window, m_towers)
	
	m_towerManager.handleEvent(e, window, m_path);
}

bool World::getBoolTowerBeingPlaced() { return m_towerManager.getbTowerBeingPlaced(); }
void World::setBoolTowerBeingPlaced(bool tf)
{
	m_towerManager.setbTowerBeingPlaced(tf);
}

void World::setdummyTowerProperties(attackType type, int strength)
{
	// not necessary to set dummy tower position until checking position compatibility
	m_towerManager.getDummyTower()->storeLogicData(type, strength);

	m_towerManager.getDummyTower()->storeGraphicsData_Cursor();
}

void World::createOrthoPath(int numInternalVertices)
{
	clearScene();
	m_path.createOrthoPath(numInternalVertices);
}

void World::createRandomPath(int numInternalVertices)
{
	clearScene();
	m_path.createRandomPath(numInternalVertices);

}
void World::clearScene()
{
	m_path.clear();
	m_towerManager.getTowers()->clear();
	m_enemies.clear();
	m_waveManager.reset();
}

void World::requestStartWave()
{
	if (m_path.getLength() != 0)
	{
		if (m_waveManager.getbWaveOngoing())
		{
			m_waveManager.setbStartWaveRequested(false);
		}
		else
		{
			m_waveManager.setbStartWaveRequested(true);
		}
	}
}

void World::update(const sf::RenderWindow& window)
{
	m_towerManager.update(window, m_path, &m_enemies);
	
	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies.at(i)->update();
		if (!m_enemies.at(i)->getbIsAlive()) { m_enemies.erase(m_enemies.begin() + i); }
	}

	m_waveManager.updatebWaveOngoing(m_enemies.size());

	// see if we can start the next wave
	if (m_waveManager.getbStartWaveRequested())
	{
		if (!m_waveManager.getbWaveOngoing())
		{
			m_waveManager.startWave();
		}
	}

	// see if we can send an enemy
	if (m_waveManager.bShouldInstantiateEnemies()) //TODO: can allow for different sets of path vertices to be given to enemies
	{
		m_waveManager.instantiateEnemies(&m_enemies, m_path.getVertices());
	}
}

void World::render(sf::RenderTarget& renderer)
{
	m_path.render(renderer);

	m_towerManager.render(renderer);
	
	for (const auto& obj : m_enemies)
	{
		obj->render(renderer);
	}
}

void World::handleInput()
{

}


