#include "WorldManager.h"
#include "Enemy.h"

#include "Util\Random.h"
#include <iostream>

WorldManager::WorldManager()
{
	m_enemyReleaseDelayTime = sf::milliseconds(500);
	m_constructWaveGeneratingData();
	reset();
}

void WorldManager::m_constructWaveGeneratingData()
{
	// TODO: wave 1: 1s for -1 tower practice
	// wave 2: 2s for /2 tower practice (do not allow it to be completed with -1s)
	// wave 3: 3s for /3 tower practice
	// wave 4: 4s for sqrt tower practice
	// wave 5: primes (2, 3, 5) -- in general, if n is prime then have the nth wave be a wave of primes
	// OR, every 5th wave is a wave of only primes, increasing in the number of enemies?

	m_waveGeneratingData =
	{
		std::make_pair<std::vector<int>, int>({ 33 }, 70),
		std::make_pair<std::vector<int>, int>({ 28 }, 10),
		std::make_pair<std::vector<int>, int>({ 3 }, 10),
		std::make_pair<std::vector<int>, int>({ 4 }, 10),
		std::make_pair<std::vector<int>, int>({ 2, 3, 5 }, 15),
		std::make_pair<std::vector<int>, int>({ 3, 6, 9 }, 15),
		std::make_pair<std::vector<int>, int>({ 2, 4, 6, 8, 10 }, 15),
		std::make_pair<std::vector<int>, int>({ 3, 5, 7, 9 }, 15),
		std::make_pair<std::vector<int>, int>({ 4, 5, 6, 7, 8, 9, 10 }, 15),
		std::make_pair<std::vector<int>, int>({ 2, 3, 5, 7, 11, 13, 17, 19 }, 20),
		std::make_pair<std::vector<int>, int>({ 4, 9, 16, 25, 36, 49 }, 20),
		std::make_pair<std::vector<int>, int>({ 2, 6, 10, 14, 18, 22, 26 }, 20),
		std::make_pair<std::vector<int>, int>({ 50 }, 20),
		std::make_pair<std::vector<int>, int>({ 29 }, 20),
		std::make_pair<std::vector<int>, int>({ 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 61 }, 25),
		std::make_pair<std::vector<int>, int>({ 8, 27, 64, 125, 216, 343, 512 }, 25),
		std::make_pair<std::vector<int>, int>({ 99 }, 25),
		std::make_pair<std::vector<int>, int>({ 101 }, 25),
		std::make_pair<std::vector<int>, int>({ 173 }, 25),
		std::make_pair<std::vector<int>, int>({ 23, 29, 31, 37, 41, 43, 47, 53, 61, 67, 71, 73, 79, 83, 89, 91, 97, 101, 103 }, 30)
	};
}

void WorldManager::reset()
{
	m_path.clear();
	m_towerManager.reset();
	m_enemies.clear();
	m_currWave.clear();
	m_prevWave.clear();

	m_numLives = 10;
	m_waveNumber = 0; // waveNumber value is 1 less than wave # known by player (0 is wave #1, 1 is wave #2, etc)
	m_bWaveOngoing = false;
	m_bStartWaveRequested = false;
	m_bShouldInstantiateEnemies = false;
	m_numOfEnemiesStarted = 0;
	m_timer.restart();
	m_timePoint = m_timer.getElapsedTime();
}

void WorldManager::requestStartWave()
{
	if (m_bWaveOngoing)
	{
		m_bStartWaveRequested = false;
	}
	else
	{
		m_bStartWaveRequested = true;
	}
}

const int WorldManager::getNumLives() const { return m_numLives; }
const int WorldManager::getWaveNumber() const { return m_waveNumber; }

void WorldManager::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
	m_towerManager.handleEvent(e, window, m_path);

	for (const auto& obj : m_enemies)
	{
		obj->handleEvent(e, window);
	}

	if (e.type == sf::Event::EventType::MouseButtonReleased)
	{
		sf::Vector2f clickPos = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

		m_handleEvent_EnemySelection(clickPos);

	}
}

void WorldManager::render(sf::RenderTarget& renderer)
{
	m_path.render(renderer);
	m_towerManager.render(renderer);

	for (const auto& obj : m_enemies)
	{
		obj->render(renderer);
	}
}

void WorldManager::update(const sf::RenderWindow& window)
{
	m_towerManager.update(window, m_path, &m_enemies);

	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies.at(i)->update(window);
		if (!m_enemies.at(i)->getbIsAlive())
		{
			m_enemies.erase(m_enemies.begin() + i);
		}
		else if (m_enemies.at(i)->getbReachedTheEnd())
		{
			m_numLives--;
			m_enemies.erase(m_enemies.begin() + i);
		}
	}

	if (m_enemies.size() > 0) { m_bWaveOngoing = true; }
	else { m_bWaveOngoing = false; }

	if (m_bStartWaveRequested) // see if we can start the next wave
	{
		if (!m_bWaveOngoing)
		{
			startWave();
		}
	}
	
	if (m_bShouldInstantiateEnemies) // see if we can send an enemy
									 //TODO: can allow for different sets of path vertices to be given to enemies
	{
		instantiateEnemies(&m_enemies, m_path.getVertices());
	}
}

void WorldManager::startWave()
{
	m_generateAndStoreWave(m_waveNumber);
	m_bShouldInstantiateEnemies = true;
	m_bStartWaveRequested = false;
}

void WorldManager::m_generateAndStoreWave(int waveNumber)
{
	if (m_waveNumber != 0)
	{
		m_prevWave = m_currWave; // for wave stats.. TODO: display some prev wave stats after each wave (or make a button for it, etc)
		m_currWave.clear();
	}

	static Random<> rand;

	for (int i = 0; i < m_waveGeneratingData.at(waveNumber).second; i++) // # of enemy profiles to create
	{
		// number representing either the 1st, 2nd, 3rd, .. up to nth element of m_waveGeneratingData's vector for this wave
		int enemySelectionIndex = rand.getIntInRange(0, m_waveGeneratingData.at(waveNumber).first.size() - 1);

		int enemyHealth = m_waveGeneratingData.at(waveNumber).first.at(enemySelectionIndex);

		m_currWave.push_back(std::make_pair(enemyHealth, (float)1.5));
	}
}

void WorldManager::instantiateEnemies(std::vector<std::unique_ptr<Enemy>> *enemies, const std::vector<sf::Vector2f>& vertices)
{
	//trigger for next wave to begin (and wavenumber to increase) is a click on "start wave", which makes bCanInstantiateEnemies true
	//this function only gets entered when bCanInstantiateEnemies is true

	m_elapsedTime = m_timer.getElapsedTime() - m_timePoint;
	if (m_elapsedTime > m_enemyReleaseDelayTime && m_numOfEnemiesStarted < (signed)m_currWave.size())
	{
		m_timePoint = m_timer.getElapsedTime();

		// when instantiating an enemy here, instead of only health, can specify 2 arguments: m_currWave.at(m_waveNumber).first, m_currWave.at(m_waveNumber).second
		// this would look better if instead of first and second, we selected "health" and "speed" as members of a struct

		enemies->push_back(std::make_unique<Enemy>(vertices, m_currWave.at(m_numOfEnemiesStarted).first,
			m_currWave.at(m_numOfEnemiesStarted).second)); // instantiate an enemy
		m_numOfEnemiesStarted++;
	}

	if (m_numOfEnemiesStarted == m_currWave.size()) // all enemies for this wave have been started
	{
		m_bShouldInstantiateEnemies = false; //don't enter this entire function again until the player clicks the button again
		m_numOfEnemiesStarted = 0; //reset this value

								   //waveNumber=0 is wave#1, waveNumber=1 is wave#2, etc.
		if (m_waveNumber != m_waveGeneratingData.size() - 1)
		{
			m_waveNumber++; // should actually increase wavenumber only when all enemies are !alive
		}
	}
}

Cursor* WorldManager::getDummyTower() { return m_towerManager.getDummyTower(); }

const bool& WorldManager::getbTowerBeingPlaced() const
{
	return m_towerManager.getbTowerBeingPlaced();
}

void WorldManager::setbTowerBeingPlaced(bool tf)
{
	m_towerManager.setbTowerBeingPlaced(tf);
}

void WorldManager::createOrthoPath(int numInternalVertices)
{
	m_path.createOrthoPath(numInternalVertices);
}

void WorldManager::createRandomPath(int numInternalVertices)
{
	m_path.createRandomPath(numInternalVertices);
}


// TODO: use this function (m_handleEvent_ObjectSelection) for both Enemy and Tower selection
void WorldManager::m_handleEvent_EnemySelection(const sf::Vector2f& clickPos)
{
	bool bClickedOffOfEnemy = true; // will remain true unless an enemy is found that was clicked on

	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		if (distanceBetweenPoints(m_enemies.at(i)->getPosition(), clickPos) < m_enemies.at(i)->getRadius()) // TODO: change size into radius
			// then the enemy at position i is the enemy that has been clicked on
		{
			bClickedOffOfEnemy = false; // false, because we have seen that the click was ON a enemy

			if (m_enemies.at(i)->getbIsClickedOn()) // enemy that was selected has been clicked on again
			{
				m_enemies.at(i)->setbIsClickedOn(false);
				break; // an enemy that was selected has been deselected; no need to do anything else with the existing enemies
			}
			else // the clicked enemy was not previously selected, so deselect any prev. selected enemies and select the one at i
			{
				// deselect all enemies...
				for (unsigned int k = 0; k < m_enemies.size(); k++)
				{
					m_enemies.at(k)->setbIsClickedOn(false);
				}
				// ...then select the new one
				m_enemies.at(i)->setbIsClickedOn(true);
			}
		}
	}

	if (bClickedOffOfEnemy)
	{
		for (unsigned int k = 0; k < m_enemies.size(); k++)
		{
			m_enemies.at(k)->setbIsClickedOn(false);
		}
	}
}



