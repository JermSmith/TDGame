#include "World.h"
#include "Path.h"

World::World()
{
	m_numLives = 10;
}

void World::handleEvent(sf::Event e, const sf::RenderWindow& window)
{	
	m_towerManager.handleEvent(e, window, m_path);
	m_waveManager.handleEvent(e, window);
}

bool World::getBoolTowerBeingPlaced() { return m_towerManager.getbTowerBeingPlaced(); }
void World::setBoolTowerBeingPlaced(bool tf)
{
	m_towerManager.setbTowerBeingPlaced(tf);
}

void World::setdummyTowerProperties(attackType type, int strength, sf::Vector2f position)
{
	m_towerManager.getDummyTower()->setBasicProperties(type, strength, position);
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
	m_towerManager.getTowersVector()->clear();
	m_waveManager.getEnemiesVector()->clear();
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
	m_towerManager.update(window, m_path, m_waveManager.getEnemiesVector());
	m_waveManager.update(m_path.getVertices(), window);
}

void World::render(sf::RenderTarget& renderer)
{
	m_path.render(renderer);
	m_towerManager.render(renderer);
	m_waveManager.render(renderer);
}

void World::handleInput()
{

}


