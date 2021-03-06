#pragma once
#include <SFML\Graphics.hpp>
#include "GameObjects\Tower.h"

class TowerRoot : public Tower
{
public:
	TowerRoot(const sf::RenderWindow& window, const attackType& type, int strength, const sf::Vector2f& position, float radius, int pointCount);

	void updateAtakTimer_FindEnems_CreateProj(const std::vector<std::unique_ptr<Enemy>>& enemies) override;


private:
	void generateWidgets(const sf::RenderWindow&);

	void populateHoverMenu();
	void populateUpgradeMenu() override;

};


