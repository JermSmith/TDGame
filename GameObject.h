#pragma once
#include <SFML\Graphics.hpp>
#include <vector>


class GameObject
{
public:
	const sf::Vector2f& getPosition() const;
	const sf::Vector2f& getSize() const;

	void setPosition(sf::Vector2f& position);
	void setSize(sf::Vector2f& size);

	virtual void handleEvent(sf::Event e, const sf::RenderWindow& window) {};
	//virtual void update() = 0;
	virtual void render(sf::RenderTarget& renderer) = 0;

protected:
	sf::Vector2f m_position;
	sf::Vector2f m_size;
};
