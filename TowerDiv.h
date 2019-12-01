#pragma once
#include <SFML\Graphics.hpp>
#include "GameObjects\Tower.h"

class TowerDiv : public Tower
{
public:

	TowerDiv(const sf::RenderWindow& window, attackType type, int strength);

	void update(std::vector<std::unique_ptr<Enemy>>* enemies);

private:
	void m_attackEnemies(std::vector<std::unique_ptr<Enemy>>* enemies);

};

