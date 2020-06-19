#pragma once
#include <SFML\Graphics.hpp>
#include "GameObjects\Tower.h"

class TowerDiv : public Tower
{
public:
	TowerDiv(const attackType& type, const int& strength, const sf::Vector2f& position, const float& radius, const int& pointCount);

	void updateAttackLogic(std::vector<std::unique_ptr<Enemy>>* enemies) override;

private:
	void m_attackEnemies(std::vector<std::unique_ptr<Enemy>>* enemies);

};


