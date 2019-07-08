#include "World.h"

#include "Math.h"
#include "WaveManager.h"

#include "GameObjects\Path.h"
#include "GameObjects\Tower.h"
#include "GameObjects\Enemy.h"

World::World()
{
	
}

void World::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
	if (e.type == sf::Event::EventType::MouseButtonReleased && m_bTowerBeingPlaced)
	{
		//create a new object in testNewGameObject to test if it works, and if so remove it from testNewGameObject and make a new one in gameObjects
		m_testNewTower.push_back(std::make_unique<Tower>(window));

		if (!m_testNewTower.back()->bInterferesWithScene(m_towers, m_path, window))
		{
			//no interference found with new object and path, so can place object
			m_testNewTower.pop_back();
			m_towers.push_back(std::make_unique<Tower>(window)); // "move" the test tower to the vector of towers
			//TODO: this construction of a tower can include more arguments than the checking tower - it should include range and type of attack
			m_bTowerBeingPlaced = false;
		}
		else
		{
			m_testNewTower.pop_back();
		}
	}
}

bool World::getBoolTowerBeingPlaced() { return m_bTowerBeingPlaced; }
void World::setBoolTowerBeingPlaced(bool b)
{
	m_bTowerBeingPlaced = b;
}

void World::createOrthoPath()
{
	clearScene();
	m_path.createOrthoPath(4);
}

void World::createRandomPath()
{
	clearScene();
	m_path.createRandomPath(4);

}
void World::clearScene()
{
	m_path.clear();
	m_towers.clear();
	m_enemies.clear();
	m_waveManager.reset();
}

void World::allowInstantiatingEnemies() { m_waveManager.setbCanInstantiateEnemies(true); }

void World::update(sf::Time deltaTime, const sf::RenderWindow& window)
{
	for (unsigned int i = 0; i < m_towers.size(); i++)
	{
		m_towers.at(i)->update();
	}
	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies.at(i)->update();
	}

	//TODO:
	//for each tower (this would happen in the tower class, not here - it would happen in tower->update),
	//loop through the list of enemies and calculate the distance. if the distance is smaller than the range of the tower,
	//then attack the enemy. m_enemies will need to be passed into m_towers->update(m_enemies)

	// instantiate enemies -- TODO: can allow for different sets of path vertices to be given to enemies
	if (m_waveManager.getbCanInstantiateEnemies() && m_path.getLength() > 0)
	{
		m_waveManager.instantiateEnemies(&m_enemies, &m_path.getVertices());
	}

	updateCursor(window);

}

void World::updateCursor(const sf::RenderWindow& window)
{
	if (m_bTowerBeingPlaced)
	{
		//create a new object in testNewGameObject at the current mouse position to check what color the cursor circle should be
		m_testNewTower.push_back(std::make_unique<Tower>(window));

		if (!m_testNewTower.back()->bInterferesWithScene(m_towers, m_path, window))
		{
			m_cursor.updatePositive(window); //possible to place tower here
			m_testNewTower.pop_back(); //remove the new tower from the back of m_testNewTower since color of cursor has been decided
		}
		else
		{
			m_cursor.updateNegative(window); //not possible to place tower here
			m_testNewTower.pop_back(); //remove the new tower from the back of m_testNewTower since color of cursor has been decided
		}
	}
	else
	{
		m_cursor.hide(); //do not show a circle around radius, since no tower is being placed
	}
}

void World::render(sf::RenderTarget& renderer)
{
	m_path.render(renderer);

	for (const auto& obj : m_towers)
	{
		obj->render(renderer);
	}
	for (const auto& obj : m_enemies)
	{
		obj->render(renderer);
	}

	m_cursor.render(renderer);

}

void World::handleInput()
{

}