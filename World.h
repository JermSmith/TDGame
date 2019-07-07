#pragma once

#include "GameObjects\GameObject.h"
#include "GUI\Cursor.h"
#include <memory>

class World
{
public:

	World();
	
	void handleEvent(sf::Event e, const sf::RenderWindow& window);
	void handleInput();
	void update(sf::Time deltaTime, const sf::RenderWindow& window);
	void fixedUpdate(sf::Time deltaTime);
	void render(sf::RenderTarget& renderer);

	void createOrthoPath();
	void createRandomPath();
	void clearScene();

	void instantiateEnemies();

	void setBoolTowerBeingPlaced(bool tf);
	bool getBoolTowerBeingPlaced();

	//std::vector<std::unique_ptr<GameObject>> getGameObjects();
	//Path getPath();

	//void addGameObject(std::unique_ptr<GameObject>);
	//void setGameObjects(std::vector<std::unique_ptr<GameObject>>);
	//void setPath(Path);

	bool bInterferesWithScene(
		std::unique_ptr<GameObject>& newObj, std::vector<std::unique_ptr<GameObject>>& gameObjects, Path& path, const sf::RenderWindow& window);


private:

	Path m_path;
	// should eventually use this path and vector of gameobjects to replace the ones in stateplaying, then stateplaying can access through world.getPath or world.getGameObjects

	std::vector<std::unique_ptr<GameObject>> m_testNewGameObject; // vector to contain new game object while checking compatibility
	std::vector<std::unique_ptr<GameObject>> m_gameObjects;
	
	bool m_bTowerBeingPlaced = false;

	Cursor m_cursor;
	void updateCursor(const sf::RenderWindow& window);

};