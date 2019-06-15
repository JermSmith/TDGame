#pragma once
#include <SFML\Graphics.hpp>

class Cursor
{
public:
	Cursor();

	//void handleEvent(sf::Event e, const sf::RenderWindow& window);
	//void update(sf::Time deltaTime);
	//void fixedUpdate(sf::Time deltaTime);
	void render(sf::RenderTarget& renderer);

	void hide();
	void updatePositive(const sf::RenderWindow& window);
	void updateNegative(const sf::RenderWindow& window);

	void setRadius(float& radius);

	float getRadius();

private:
	sf::CircleShape m_cursorCircle;

};