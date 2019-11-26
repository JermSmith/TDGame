#pragma once

#include "TowerSub.h"
#include "TowerDiv.h"
#include "TowerRoot.h"
#include "Tower.h"
#include "GUI\Cursor.h"

class TowerManager
{
public:
	TowerManager();

	void update(const sf::RenderWindow& window, const Path& path, std::vector<std::unique_ptr<Enemy>>* enemies);
	void handleEvent(sf::Event e, const sf::RenderWindow& window, const Path& path);
	void render(sf::RenderTarget& renderer);

	std::vector<std::unique_ptr<Tower>>* getTowersVector();
	Cursor* getDummyTower();

	const bool& getbTowerBeingPlaced() const;
	void setbTowerBeingPlaced(bool tf);


private:
	std::vector<std::unique_ptr<Tower>> m_towers; // vector of all towers
	// (ordered as strong root -> weak root -> strong div -> weak div -> strong sub -> strong add)

	Cursor m_dummyTower; // tower to check placement compatibility and update cursor

	bool m_bTowerBeingPlaced = false;

	void m_handleEvent_TowerSelection(const sf::RenderWindow&);
	void m_handleEvent_InsertDummyTowerIntoVectorOfTowers(const sf::RenderWindow&);
};


