#pragma once
#include "Enemy.h"
#include "TowerManager.h"
#include "Path.h"
#include <memory>


class WorldManager
{
public:
	WorldManager();

	void reset();

	void requestStartWave();

	const int getNumLives() const;
	const int getWaveNumber() const;

	void handleEvent(sf::Event e, const sf::RenderWindow& window);
	void render(sf::RenderTarget& renderer);
	void update(const sf::RenderWindow& window);

	Cursor* getDummyTower();
	const bool& getbTowerBeingPlaced() const;
	void setbTowerBeingPlaced(bool tf);

	void createOrthoPath(int numInternalVertices);
	void createRandomPath(int numInternalVertices);

private:
	void m_constructWaveGeneratingData();
	std::vector<std::pair<std::vector<int>, int>> m_waveGeneratingData;

	TowerManager m_towerManager;
	Path m_path;

	std::vector<std::unique_ptr<Enemy>> m_enemies;
	std::vector<std::pair<int, float>> m_currWave; // each pair is an enemy with two properties: health(int) and speed(float)
	std::vector<std::pair<int, float>> m_prevWave; // for wave stats

	sf::Clock m_timer;
	sf::Time m_elapsedTime;
	sf::Time m_timePoint;
	sf::Time m_enemyReleaseDelayTime;// = sf::milliseconds(500);

	int m_numLives;
	int m_waveNumber; // waveNumber value is 1 less than wave # known by player (0 is wave #1, 1 is wave #2, etc)
	int m_numOfEnemiesStarted;

	bool m_bShouldInstantiateEnemies;
	bool m_bStartWaveRequested;
	bool m_bWaveOngoing;

	void startWave();
	void m_generateAndStoreWave(int waveNumber);
	void instantiateEnemies(std::vector<std::unique_ptr<Enemy>> *enemies, const std::vector<sf::Vector2f>& vertices);

	void m_handleEvent_EnemySelection(const sf::Vector2f& clickPos);

};




