#include "WaveManager.h"
#include "GameObjects\Enemy.h"
#include <iostream>

void WaveManager::reset()
{
	m_waveNumber = 0;
	m_bWaveSending = false;
	m_bCanInstantiateEnemies = false;
	m_numOfEnemiesStarted = 0;

}

//void WaveManager::instantiateEnemies(std::vector<std::unique_ptr<GameObject>> *gameobjects, std::vector<sf::Vector2f> *vertices)
void WaveManager::instantiateEnemies(std::vector<std::unique_ptr<Enemy>> *enemies, std::vector<sf::Vector2f> *vertices) // NEW
{
	//trigger for next wave to begin (and wavenumber to increase) is a click on "start wave", which makes bCanInstantiateEnemies true
	//this function only gets entered when bCanInstantiateEnemies is true

	m_elapsedTime = m_timer.getElapsedTime() - m_timePoint;
	if (m_elapsedTime > m_delayTime && m_numOfEnemiesStarted < m_numOfEnemiesVector.at(m_waveNumber))
	{
		m_timePoint = m_timer.getElapsedTime();

		// may also choose to make another constructor for Enemy, so that more characteristics can be specified for specific waves,
		// such as types of enemies, speed, health (already included), random possibilities. These characteristics for a given wave
		// could be read from a/multiple private vectors belonging to WaveManager, so that World.cpp doesn't need to concern itself
		// with the types of waves being sent, only with sending the next wave when it is called for
		//gameobjects->push_back(std::make_unique<Enemy>(*vertices, 100)); // instantiate an enemy
		enemies->push_back(std::make_unique<Enemy>(*vertices, 100)); // instantiate an enemy // NEW
		m_numOfEnemiesStarted++;

		std::cout << "Enemy started for wave # " << m_waveNumber << std::endl;
	}

	if (m_numOfEnemiesStarted == m_numOfEnemiesVector.at(m_waveNumber)) // all enemies for this wave have been started
	{
		//waveNumber=0 is wave#1, waveNumber=1 is wave#2, etc.
		if (m_waveNumber != m_numOfEnemiesVector.size() - 1)
		{
			m_waveNumber++;
		}

		m_numOfEnemiesStarted = 0; //reset this value
		m_bCanInstantiateEnemies = false; //don't enter this entire function again until the player clicks the button again
	}
}

bool WaveManager::getbCanInstantiateEnemies() { return m_bCanInstantiateEnemies; }
void WaveManager::setbCanInstantiateEnemies(bool tf) { m_bCanInstantiateEnemies = tf; }



