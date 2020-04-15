#include "InteractableCircle.h"
#include "Util\Math.h"

/*void InteractableCircle::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
	switch (e.type)
	{
	case sf::Event::MouseMoved:
		if (isRolledOn(window))
		{
			m_circle.setFillColor(sf::Color(51, 51, 51));
		}
		else
		{
			m_circle.setFillColor(sf::Color::Black);
		}
	}
}*/

bool InteractableCircle::isRolledOn(const sf::RenderWindow& window) const
{
	auto pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	return distanceBetweenPoints(pos, m_circle.getPosition()) < m_circle.getRadius();

	//return m_shape.getGlobalBounds().contains((float)pos.x, (float)pos.y);
}

sf::CircleShape* InteractableCircle::getCircle()
{
	return &m_circle;
}

