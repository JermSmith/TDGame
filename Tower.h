#pragma once
#include "GameObject.h"

class Tower : public GameObject
{
public:
	Tower();
	Tower(sf::Vector2i position);
	Tower(const sf::RenderWindow& window);

	void handleEvent(sf::Event e, const sf::RenderWindow& window) override;
	void update() override;
	void render(sf::RenderTarget& renderer) override;


private:


	sf::CircleShape m_circle;


};