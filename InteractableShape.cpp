#include "InteractableShape.h"
#include "Util\Math.h"

InteractableShape::InteractableShape(const float& radius, const int& pointCount)
{
	defineShape(radius, pointCount);
}

InteractableShape::InteractableShape(const float& width, const float& height)
{
	defineShape(width, height);
}

void InteractableShape::defineShape(const float& radius, const int& pointCount)
{
	m_shape.setPointCount(pointCount);
	float theta = 0; // angle in radians
	for (int p = 0; p < (signed)m_shape.getPointCount(); p++)
	{
		float x = radius * cosf(theta);
		float y = radius * sinf(theta);

		m_shape.setPoint(p, sf::Vector2f(x, y));

		theta = theta + 2 * PI / m_shape.getPointCount(); // incrementing the angle getPointCount times makes one revolution
	}
}

void InteractableShape::defineShape(const float& width, const float& height)
{
	m_shape.setPointCount(4);
	m_shape.setPoint(0, sf::Vector2f(width / 2., -height / 2.)); // top right
	m_shape.setPoint(1, sf::Vector2f(-width / 2., -height / 2.)); // top left
	m_shape.setPoint(2, sf::Vector2f(-width / 2., height / 2.)); // bottom left
	m_shape.setPoint(3, sf::Vector2f(width / 2., height / 2.)); // bottom right
}

int InteractableShape::getPointCount() const
{
	return m_shape.getPointCount();
}

bool InteractableShape::isRolledOn(const sf::RenderWindow& window) const
{
	auto pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	if (m_shape.getPointCount() > 4) // for a >5-gon
	{
		return (distanceBetweenPoints(pos, m_shape.getPosition()) < getPrimaryDim());
	}
	else // for a rectangle
	{
		return m_shape.getGlobalBounds().contains((float)pos.x, (float)pos.y);
	}
}

void InteractableShape::render(sf::RenderTarget& renderer)
{
	renderer.draw(m_shape); // TODO: make this render function const
}

float InteractableShape::getPrimaryDim() const
{
	if (m_shape.getPointCount() > 4) // for a circle, or at least a pentagon
	{
		return distanceBetweenPoints(m_shape.getOrigin(), m_shape.getPoint(0)); // from centre to a point
	}
	else if (m_shape.getPointCount() == 4)
	{
		return distanceBetweenPoints(m_shape.getPoint(0), m_shape.getPoint(1)) / 2; // half of width of rectangle
	}
	else
	{
		//throw "Cannot compute InteractableShape::getPrimaryDim(). InteractableShape is made up of fewer than 4 points.";
	}
}

sf::FloatRect InteractableShape::getGlobalBounds() const
{
	return m_shape.getGlobalBounds();
}

void InteractableShape::setOrigin(const sf::Vector2f& origin)
{
	m_shape.setOrigin(origin);
}

void InteractableShape::setPosition(const sf::Vector2f& position)
{
	m_shape.setPosition(position);
}

sf::Color InteractableShape::getFillColour() const
{
	return m_shape.getFillColor();
}

void InteractableShape::setFillColour(const sf::Color& colour)
{
	m_shape.setFillColor(colour);
}

void InteractableShape::setOutlineThickness(const float& thickness)
{
	m_shape.setOutlineThickness(thickness);
}

void InteractableShape::setOutlineColour(const sf::Color& colour)
{
	m_shape.setOutlineColor(colour);
}

void InteractableShape::setTexture(const sf::Texture& tex)
{
	m_shape.setTexture(&tex);
}






