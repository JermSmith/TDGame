#pragma once
#include <SFML\Graphics.hpp>

class InteractableShape
{
public:
	//virtual void handleEvent(sf::Event e, const sf::RenderWindow& window) = 0;

	virtual bool isRolledOn(const sf::RenderWindow& window) const = 0;
	//virtual bool isClicked(const sf::RenderWindow& window) const = 0;

protected:
	sf::ConvexShape m_shape;

};