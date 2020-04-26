#pragma once
#include <SFML\Graphics.hpp>
#include "GameObjects\Tower.h"

/* The main function of Cursor is its ability to check for interference of the scene and a new tower. */
class Cursor : public Tower
{
public:
	Cursor();

	void update(const sf::RenderWindow& window, const Path& path, const std::vector<std::unique_ptr<Tower>>& towers,
		bool bTowerBeingPlaced); // NOT inherited from tower class

	void render(sf::RenderTarget& renderer);

	bool bInterferesWithScene(const std::vector<std::unique_ptr<Tower>>& towers, const Path& path);


private:
	void updatePositive();
	void updateNegative();
	void hide();

};

