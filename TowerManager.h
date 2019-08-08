#pragma once

#include "Tower.h"
#include "GUI\Cursor.h"

class TowerManager
{
public:
	TowerManager();

	void update(const sf::RenderWindow& window, const Path& path, std::vector<std::unique_ptr<Enemy>>* enemies);
	void handleEvent(sf::Event e, const sf::RenderWindow& window, const Path& path);
	void render(sf::RenderTarget& renderer);


	std::vector<std::unique_ptr<Tower>>* getTowers();
	Cursor* getDummyTower();


	const bool& getbTowerBeingPlaced() const;
	void setbTowerBeingPlaced(bool tf);


private:

	std::vector<std::unique_ptr<Tower>> m_towers;

	Cursor m_dummyTower; // tower to check placement compatibility and update cursor

	bool m_bTowerBeingPlaced = false;


};