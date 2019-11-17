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

	std::vector<std::unique_ptr<Tower>>* getDivRootTowers();
	std::vector<std::unique_ptr<Tower>>* getSubAddTowers();
	Cursor* getDummyTower();

	const bool& getbTowerBeingPlaced() const;
	void setbTowerBeingPlaced(bool tf);


private:

	std::vector<std::unique_ptr<Tower>> m_divRootTowers; // vector of division and root towers
	std::vector<std::unique_ptr<Tower>> m_subAddTowers; // vector of subtraction and addition towers

	Cursor m_dummyTower; // tower to check placement compatibility and update cursor

	bool m_bTowerBeingPlaced = false;

	bool m_bTowerWasJustSelected = false; // remains false if a tower was just deselected
	void m_handleEvent_TowerSelection(const sf::RenderWindow&);
	void m_handleEvent_TowerSelection_LoopTowers(const sf::RenderWindow& window, 
		std::vector<std::unique_ptr<Tower>>* towersVector);
	void m_handleEvent_InsertDummyTowerIntoVectorOfTowers(const sf::RenderWindow&);
};

