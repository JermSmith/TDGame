#pragma once

#include "WaveManager.h"
//#include "GameObjects\GameObject.h"
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

	//std::vector<std::unique_ptr<GameObject>> getGameObjects();
	//Path getPath();

	//void addGameObject(std::unique_ptr<GameObject>);
	//void setGameObjects(std::vector<std::unique_ptr<GameObject>>);
	//void setPath(Path);

	/*bool bInterferesWithScene(
		std::unique_ptr<GameObject>& newObj, std::vector<std::unique_ptr<GameObject>>& gameObjects, Path& path, const sf::RenderWindow& window);*/
	bool bTowerInterferesWithScene(
		std::unique_ptr<Tower>& newTower, std::vector<std::unique_ptr<Tower>>& Towers, Path& path, const sf::RenderWindow& window);


private:

	Path m_path;
	// should eventually use this path and vector of gameobjects to replace the ones in stateplaying, then stateplaying can access through world.getPath or world.getGameObjects

	WaveManager m_waveManager;

	//std::vector<std::unique_ptr<GameObject>> m_testNewGameObject; // vector to contain new game object while checking compatibility
	//std::vector<std::unique_ptr<GameObject>> m_gameObjects;

	std::vector<std::unique_ptr<Tower>> m_testNewTower; // vector to contain new tower while checking compatibility
	std::vector<std::unique_ptr<Tower>> m_towers;
	std::vector<std::unique_ptr<Enemy>> m_enemies;
	
	bool m_bTowerBeingPlaced = false;

	Cursor m_cursor;
	void updateCursor(const sf::RenderWindow& window);

};