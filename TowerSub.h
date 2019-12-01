#pragma once
#include <SFML\Graphics.hpp>
#include "GameObjects\Tower.h"

class TowerSub : public Tower
{
public:

	TowerSub(const sf::RenderWindow& window, attackType type, int strength);

	void update(std::vector<std::unique_ptr<Enemy>>* enemies);

private:
	void m_attackEnemies(std::vector<std::unique_ptr<Enemy>>* enemies);

};

