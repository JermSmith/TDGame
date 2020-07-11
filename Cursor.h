#pragma once
#include <SFML\Graphics.hpp>
#include "GameObjects\Tower.h"

/* The main function of Cursor is its ability to check for interference of the scene and a new tower. */
class Cursor : public Tower
{
public:
	Cursor(const sf::RenderWindow& window);

	void update(const sf::RenderWindow& window, const Path& path, const std::vector<std::unique_ptr<Tower>>& towers,
		bool bTowerBeingPlaced); // NOT inherited from tower class

	void render(sf::RenderTarget& renderer);

	bool bInterferesWithScene(const std::vector<std::unique_ptr<Tower>>& towers, const Path& path);

	void populateHoverMenu() override;
	void hideHoverMenu();

private:
	void generateWidgets(const sf::RenderWindow&) override;
	void populateStatsMenu() override;

	void updatePositive();
	void updateNegative();
	void hide();

};

