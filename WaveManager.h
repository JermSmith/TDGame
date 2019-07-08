#pragma once
//#include "GameObjects\GameObject.h"
#include "GameObjects\Enemy.h"
#include "GameObjects\Path.h"
#include <memory>


class WaveManager
{
public:
	void reset();

	//void instantiateEnemies(std::vector<std::unique_ptr<GameObject>> *gameobjects, std::vector<sf::Vector2f> *vertices);
	void instantiateEnemies(std::vector<std::unique_ptr<Enemy>> *enemies, std::vector<sf::Vector2f> *vertices);

	bool getbCanInstantiateEnemies();
	void setbCanInstantiateEnemies(bool);


private:
	bool m_bCanInstantiateEnemies = false;
	bool m_bWaveSending = false;
	
	// waveNumber value is 1 less than wave # known by player (0 is wave #1, 1 is wave #2, etc)
	int m_waveNumber = 0; 

	int m_numOfEnemiesStarted = 0;

	std::vector<int> m_numOfEnemiesVector = { 3, 2, 3, 4, 5 };

	sf::Clock m_timer;
	sf::Time m_elapsedTime;
	sf::Time m_timePoint = m_timer.restart();
	sf::Time m_delayTime = sf::milliseconds(500);

};


