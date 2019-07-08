#pragma once

#include "WaveManager.h"
#include "GameObjects\Tower.h"
#include "GameObjects\Enemy.h"
#include "GUI\Cursor.h"
#include <memory>

class World
{
public:

	World();
	
	void handleEvent(sf::Event e, const sf::RenderWindow& window);
	void handleInput();
	void update(sf::Time deltaTime, const sf::RenderWindow& window);
	//void fixedUpdate(sf::Time deltaTime);
	void render(sf::RenderTarget& renderer);

	void createOrthoPath();
	void createRandomPath();
	void clearScene();

	void allowInstantiatingEnemies();

	void setBoolTowerBeingPlaced(bool tf);
	bool getBoolTowerBeingPlaced();


private:

	Path m_path;
	// should eventually use this path and vector of gameobjects to replace the ones in stateplaying, then stateplaying can access through world.getPath or world.getGameObjects

	WaveManager m_waveManager;

	std::vector<std::unique_ptr<Tower>> m_testNewTower; // vector to contain new tower while checking compatibility
	std::vector<std::unique_ptr<Tower>> m_towers;
	std::vector<std::unique_ptr<Enemy>> m_enemies;
	
	bool m_bTowerBeingPlaced = false;

	Cursor m_cursor;
	void updateCursor(const sf::RenderWindow& window);

};