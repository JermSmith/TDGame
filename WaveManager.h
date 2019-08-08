#pragma once
#include "Enemy.h"
#include "Path.h"
#include <memory>


class WaveManager
{
public:
	WaveManager();

	void reset();

	void updatebWaveOngoing(int sizeOfEnemyVector);

	void instantiateEnemies(std::vector<std::unique_ptr<Enemy>> *enemies, const std::vector<sf::Vector2f>& vertices);

	bool bShouldInstantiateEnemies();

	bool getbWaveOngoing() const;

	void setbStartWaveRequested(bool);
	bool getbStartWaveRequested() const;

	void startWave();


private:
	bool m_bShouldInstantiateEnemies;
	bool m_bStartWaveRequested;
	bool m_bWaveOngoing;
	
	int m_waveNumber; // waveNumber value is 1 less than wave # known by player (0 is wave #1, 1 is wave #2, etc)
	int m_numOfEnemiesStarted;


	void m_constructWaveGeneratingData();

	void m_generateAndStoreWave(int waveNumber);

	std::vector<std::pair<int, float>> m_currWave; // each pair is an enemy with two properties: health(int) and speed(float)
	std::vector<std::pair<int, float>> m_prevWave;

	std::vector<std::pair<std::vector<int>, int>> m_waveGeneratingData;

	sf::Clock m_timer;
	sf::Time m_elapsedTime;
	sf::Time m_timePoint;
	sf::Time m_enemyReleaseDelayTime = sf::milliseconds(500);

};


