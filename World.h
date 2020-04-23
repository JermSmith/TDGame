#pragma once

#include "Tower.h"
#include "Enemy.h"
#include "WaveManager.h"
#include "TowerManager.h"
#include "GUI\Cursor.h"
#include <memory>

class World
{
public:

	World();
	
	void handleEvent(sf::Event e, const sf::RenderWindow& window);
	void handleInput();
	void update(const sf::RenderWindow& window);
	void render(sf::RenderTarget& renderer);

	//void fixedUpdate(sf::Time deltaTime);

	void createOrthoPath(int numInternalVertices);
	void createRandomPath(int numInternalVertices);
	void clearScene();

	void requestStartWave();

	void setBoolTowerBeingPlaced(bool tf);
	bool getBoolTowerBeingPlaced();
	void setdummyTowerProperties(attackType type, int strength, sf::Vector2f position);

	int getNumLives();


private:

	Path m_path;
	WaveManager m_waveManager;
	TowerManager m_towerManager;

	//int m_numLives;

};

