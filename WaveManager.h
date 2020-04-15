#pragma once
#include "Enemy.h"
#include "Path.h"
#include <memory>


class WaveManager
{
public:
	WaveManager();

	void reset();

	std::vector<std::unique_ptr<Enemy>>* getEnemiesVector();
	bool getbWaveOngoing() const;
	void setbStartWaveRequested(bool);

	const int getWaveNumber() const;

	void handleEvent(sf::Event e, const sf::RenderWindow& window);
	void render(sf::RenderTarget& renderer);
	void update(const std::vector<sf::Vector2f>& vertices, const sf::RenderWindow& window);

private:
	void m_constructWaveGeneratingData();
	std::vector<std::pair<std::vector<int>, int>> m_waveGeneratingData;

	std::vector<std::unique_ptr<Enemy>> m_enemies;
	std::vector<std::pair<int, float>> m_currWave; // each pair is an enemy with two properties: health(int) and speed(float)
	std::vector<std::pair<int, float>> m_prevWave;

	sf::Clock m_timer;
	sf::Time m_elapsedTime;
	sf::Time m_timePoint;
	sf::Time m_enemyReleaseDelayTime = sf::milliseconds(500);

	int m_waveNumber; // waveNumber value is 1 less than wave # known by player (0 is wave #1, 1 is wave #2, etc)
	int m_numOfEnemiesStarted;

	bool m_bShouldInstantiateEnemies;
	bool m_bStartWaveRequested;
	bool m_bWaveOngoing;

	void startWave();
	void m_generateAndStoreWave(int waveNumber);
	void instantiateEnemies(std::vector<std::unique_ptr<Enemy>> *enemies, const std::vector<sf::Vector2f>& vertices);

};


