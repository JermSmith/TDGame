#pragma once
#include <SFML\Graphics.hpp>
#include "GameObjects\Tower.h"

class TowerSub : public Tower
{
public:
	TowerSub(const attackType& type, const int& strength, const sf::Vector2f& position, const float& radius, const int& pointCount);

	void updateAtakTimer_FindEnems_CreateProj(const std::vector<std::unique_ptr<Enemy>>& enemies) override;

};


