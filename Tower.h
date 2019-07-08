#pragma once
#include "GameObject.h"
#include "Path.h"
#include <memory>

class Tower : public GameObject
{
public:
	Tower();
	Tower(sf::Vector2i position);
	Tower(const sf::RenderWindow& window);

	void handleEvent(sf::Event e, const sf::RenderWindow& window) override;
	void update() override;
	void render(sf::RenderTarget& renderer) override;

	bool bInterferesWithScene(std::vector<std::unique_ptr<Tower>>& towers, Path& path, const sf::RenderWindow& window);

	int getRange();
	void setRange(int);

	int getDivisor();
	void setDivisor(int);

private:
	
	int m_range;
	int m_divisor;

	sf::CircleShape m_circle;
	

};