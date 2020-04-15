#pragma once
#include <SFML\Graphics.hpp>
#include "GameObjects\Tower.h"

class TowerDiv : public Tower
{
public:

	TowerDiv(const attackType& type, const int& strength, const sf::Vector2f& position);

	void update(std::vector<std::unique_ptr<Enemy>>* enemies, const sf::RenderWindow& window);

private:
	void m_attackEnemies(std::vector<std::unique_ptr<Enemy>>* enemies);

};

