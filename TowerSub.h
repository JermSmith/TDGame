#pragma once
#include <SFML\Graphics.hpp>
#include "GameObjects\Tower.h"

class TowerSub : public Tower
{
public:
	TowerSub(const attackType& type, const int& strength, const sf::Vector2f& position);

	void updateAttackLogic(std::vector<std::unique_ptr<Enemy>>* enemies) override;

private:
	void m_attackEnemies(std::vector<std::unique_ptr<Enemy>>* enemies);

};


