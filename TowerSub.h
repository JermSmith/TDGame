#pragma once
#include <SFML\Graphics.hpp>
#include "GameObjects\Tower.h"

class TowerSub : public Tower
{
public:
	TowerSub(const attackType& type, const int& strength, const sf::Vector2f& position);

	void update(std::vector<std::unique_ptr<Enemy>>* enemies, const sf::RenderWindow& window);

private:
	void m_attackEnemies(std::vector<std::unique_ptr<Enemy>>* enemies);

	const int DEFAULT_COOLDOWN = 1000;
	const targetPriority DEFAULT_PRIORITY = targetPriority::first;
	const int DEFAULT_MAX_NUM_TARGETS = 4;

};


