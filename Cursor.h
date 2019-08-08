#pragma once
#include <SFML\Graphics.hpp>
#include "GameObjects\Tower.h"

class Cursor : public Tower
{
public:
	Cursor();

	//void handleEvent(sf::Event e, const sf::RenderWindow& window);
	void update(const sf::RenderWindow& window, bool bTowerBeingPlaced, const std::vector<std::unique_ptr<Tower>>& towers, const Path& path);
	void render(sf::RenderTarget& renderer);

	bool bInterferesWithScene(const std::vector<std::unique_ptr<Tower>>& towers, const Path& path, const sf::RenderWindow& window);


private:
	void updatePositive(const sf::RenderWindow& window);
	void updateNegative(const sf::RenderWindow& window);
	void hide();

};