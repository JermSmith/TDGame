#include "InteractableRectangle.h"

bool InteractableRectangle::isRolledOn(const sf::RenderWindow& window) const
{
	auto pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	return m_shape.getGlobalBounds().contains((float)pos.x, (float)pos.y);
}

